#include "client.h"
#include "chess.h"
#include "server.h"

Client::Client(struct sockaddr_in addr, int fd, int idx, Server* server) {
	_addr = addr;
	_fd = fd;
	_idx = idx;
	_name = "empty";
	_chess = NULL;
	_server = server;
	_opp_fd = -1;
	_invitor_fd = -1;
}

Client::~Client() {
	if (_chess) {
		_chess->release();
		_chess = NULL;
	}
	if (_opp_fd != -1) {
		Client* opp = _server->find_client_ptr_by_fd(_opp_fd);
		opp->_opp_fd = -1;
		opp->_state = INVITE;
		json j;
		j["opp_quit"] = true;
		std::string to_send_string = j.dump();
		send(opp->fd(), to_send_string.c_str(), to_send_string.length(), 0);
	}
}


int Client::fd() {
	return _fd;
}

int Client::idx() {
	return _idx;
}

std::string Client::name() {
	return _name;
}

void Client::transfer(json& recv_json) {
	std::string to_send_string;

	if (recv_json["get_list"] == true) {
		json j = _server->client_list(this);
		to_send_string = j.dump();
		send(_fd, to_send_string.c_str(),to_send_string.length(), 0);
		return;
	}

	switch(_state) { // todo catch error
		case CREATE: {
			if (recv_json["name"] != nullptr) {
				_name = recv_json["name"];
				json j = _server->client_list(this);
				to_send_string = j.dump();
				send(_fd, to_send_string.c_str(),to_send_string.length(), 0);
				_state = INVITE;
			}
			break;
		}
		case INVITE: {
			if (recv_json["send_to_fd"] != nullptr) {
				json j;
				_opp_fd = recv_json["send_to_fd"];
				Client* opp_ptr = _server->find_client_ptr_by_fd(_opp_fd);
				if (opp_ptr == NULL) {
					j["ok"] = false;
					j["msg"] = "opp is offline";
					_state = INVITE;
				} else if (opp_ptr->playing()) {
					j["ok"] = false;
					j["msg"] = "opp is playing now";
					_state = INVITE;
				} else {
					j["recv_from_fd"] = _fd;
					_state = WAIT_INVATE_REPLY;
					opp_ptr->_state = BE_INVITED;
					opp_ptr->_invitor_fd = _fd;
				}
				to_send_string = j.dump();
				send(_opp_fd, to_send_string.c_str(),to_send_string.length(), 0);
			}
			break;
		}
		case BE_INVITED: {
			 if (recv_json["accept"] == true) {
			 	if (recv_json["recv_from_fd"] != _invitor_fd) {
			 		_invitor_fd = -1;
			 		break; // todo
			 	}
				_opp_fd = recv_json["recv_from_fd"];
				_invitor_fd = -1;
				Client* opp_ptr = _server->find_client_ptr_by_fd(_opp_fd);
				if (opp_ptr == NULL) {
					_state = INVITE;
					json j;
					j["cancel"] = true;
					to_send_string = j.dump();
					send(_opp_fd, to_send_string.c_str(), to_send_string.length(), 0);
					break;
				}
				json j;
				if (_fd & 1) {
					j["first"] = true;
					_state = OUR_TURN;
					_chess = new Chess(this, opp_ptr); // player1 first
					opp_ptr->_state = OPP_TURN;
				} else {
					j["first"] = false;
					_state = OPP_TURN;
					_chess = new Chess(opp_ptr, this);
					opp_ptr->_state = OUR_TURN;
				}
				opp_ptr->set_chess(_chess);
				to_send_string = j.dump();
				send(_fd, to_send_string.c_str(),to_send_string.length(), 0);
				j["first"] = !j["first"];
				to_send_string = j.dump();
				send(_opp_fd, to_send_string.c_str(),to_send_string.length(), 0);
			} else if (recv_json["accept"] == false) {
				_state = INVITE;
				Client* opp_ptr = _server->find_client_ptr_by_fd(_invitor_fd);
				opp_ptr->_state = INVITE;
				json j;
				j["accept"] = false;
				to_send_string = j.dump();
				send(_invitor_fd, to_send_string.c_str(),to_send_string.length(), 0);
				_invitor_fd = -1;
			}
			break;
		}
		case WAIT_INVATE_REPLY: {
			if (recv_json["cancel"] == true) {
				Client* opp_ptr = _server->find_client_ptr_by_fd(_opp_fd);
				if (opp_ptr != NULL) {
					opp_ptr->_invitor_fd = -1;
					opp_ptr->_state = INVITE;
					json j;
					j["cancel"] = true;
					to_send_string = j.dump();
					send(_opp_fd, to_send_string.c_str(), to_send_string.length(), 0);
				}
				_opp_fd = -1;
				_state = INVITE;
			}
			break;
		}
		case OUR_TURN: {
			bool ok = _chess->move(this, 
			   			 recv_json["before_x"], 
					     recv_json["before_y"],
						 recv_json["after_x"],
					     recv_json["after_y"]);
			json j;
			if (ok) {
				if (!_chess->game_over()) {
					j["ok"] = true;
					to_send_string = j.dump();
					send(_fd, to_send_string.c_str(), to_send_string.length(), 0);
					to_send_string = recv_json.dump();
					send(_opp_fd, to_send_string.c_str(), to_send_string.length(), 0);
					_state = OPP_TURN;
				} else { // game over
					if (this == _chess->winner()) {
						j["win"] = true;
						to_send_string = j.dump();
						send(_fd, to_send_string.c_str(), to_send_string.length(), 0);
						j["win"] = false;
						to_send_string = j.dump();
						send(_opp_fd, to_send_string.c_str(), to_send_string.length(), 0);
					} else {
						j["win"] = false;
						to_send_string = j.dump();
						send(_fd, to_send_string.c_str(), to_send_string.length(), 0);
						j["win"] = true;
						to_send_string = j.dump();
						send(_opp_fd, to_send_string.c_str(), to_send_string.length(), 0);
					}
					Client* opp = _server->find_client_ptr_by_fd(_opp_fd);
					opp->_state = INVITE;
					_state = INVITE;
				}
			} else {
				j["ok"] = false;
				to_send_string = j.dump();
				send(_fd, to_send_string.c_str(), to_send_string.length(), 0);
			}
			break;
		}
		case OPP_TURN: {
			if (recv_json["ok"] == true && _chess->whose_turn() == this) {
				_state = OUR_TURN;
			}
			break;
		}
	}
}

void Client::set_chess(Chess* chess) {
	_chess = chess;
}

bool Client::playing() {
	return _chess != NULL;
}

std::string Client::state_string() {
	switch (_state) {
		case CREATE:
			return "CREATE";
		case INVITE:
			return 	"INVITE";
		case BE_INVITED:
			return 	"BE_INVITED";
		case WAIT_INVATE_REPLY:
			return 	"WAIT_INVATE_REPLY";
		case OUR_TURN:
			return 	"OUR_TURN";
		case OPP_TURN:
			return 	"OPP_TURN";
	}
	return "NULL";
}