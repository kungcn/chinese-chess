#include "client.h"
#include "chess.h"
#include "server.h"

Client::Client(struct sockaddr_in addr, int fd, Server* server) {
	_addr = addr;
	_fd = fd;
	_name = "empty";
	_chess = NULL;
	_server = server;
	_opp_fd = -1;
}

Client::~Client() {
	if (_chess) {
		_chess->release();
		_chess = NULL;
	}
	if (_opp_fd != -1) {
		Client* opp = _server->find_client_ptr_by_fd(_opp_fd);
		opp->_opp_fd = -1;
		opp->_state = GAME_OVER;
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
	switch(_state) { // todo catch error
		case CREATE: {
			_name = recv_json["name"];
			json j = _server->client_list(this);
			to_send_string = j.dump();
			send(_fd, to_send_string.c_str(),to_send_string.length(), 0);
			_state = INVITE_OR_BE_INVITED;
			break;
		}
		case INVITE_OR_BE_INVITED: {
			if (recv_json["send_to_fd"]) {
				_opp_fd = recv_json["send_to_fd"];
				json j;
				j["recv_from_fd"] = _fd;
				to_send_string = j.dump();
				send(_opp_fd, to_send_string.c_str(),to_send_string.length(), 0);
				_state = WAIT_INVATE_REPLY;
			} else if (recv_json["recv_from_fd"]) {
				_opp_fd = recv_json["recv_from_fd"];
				Client* opp_ptr = _server->find_client_ptr_by_fd(_opp_fd);
				if (opp_ptr == NULL) {
					// todo: take care of opp_ptr
					printf("!!!error\n");
				}
				json j;
				if (_fd & 1) {
					j["first"] = true;
					_state = OUR_TURN;
					_chess = new Chess(this, opp_ptr); // player1 first
				} else {
					j["first"] = false;
					_state = OPP_TURN;
					_chess = new Chess(opp_ptr, this);
				}
				opp_ptr->set_chess(_chess);
				to_send_string = j.dump();
				send(_fd, to_send_string.c_str(),to_send_string.length(), 0);
				j["first"] = !j["first"];
				to_send_string = j.dump();
				send(_opp_fd, to_send_string.c_str(),to_send_string.length(), 0);
			}
			break;
		}
		case WAIT_INVATE_REPLY: {
			to_send_string = recv_json.dump();
			send(_fd, to_send_string.c_str(),to_send_string.length(), 0);
			if (recv_json["first"] == true) {
				_state = OUR_TURN;
			} else if (recv_json["first"] == false) {
				_state = OPP_TURN;
			} else {
				// without first, bug or someone attack
			}
			break;
		}
		case OUR_TURN: {
			bool ok = _chess->move(this, 
			   			 recv_json["before_x"], 
					     recv_json["before_y"],
						 recv_json["after_x"],
					     recv_json["after_x"]);
			json j;
			bool game_over = _chess->game_over();
			if (ok) {
				if (!game_over) {
					j["ok"] = true;
					to_send_string = j.dump();
					send(_fd, to_send_string.c_str(), to_send_string.length(), 0);
					to_send_string = recv_json.dump();
					send(_opp_fd, to_send_string.c_str(), to_send_string.length(), 0);
					_state = OPP_TURN;
				} else { // game over
					if (this == _chess->winner()) {
						j["result"] = "win";
						to_send_string = j.dump();
						send(_fd, to_send_string.c_str(), to_send_string.length(), 0);
						j["result"] = "lose";
						to_send_string = j.dump();
						send(_opp_fd, to_send_string.c_str(), to_send_string.length(), 0);
					} else {
						j["result"] = "lose";
						to_send_string = j.dump();
						send(_fd, to_send_string.c_str(), to_send_string.length(), 0);
						j["result"] = "win";
						to_send_string = j.dump();
						send(_opp_fd, to_send_string.c_str(), to_send_string.length(), 0);
					}
					Client* opp = _server->find_client_ptr_by_fd(_opp_fd);
					opp->_state = GAME_OVER;
					_state = GAME_OVER;
				}
			} else {
				j["ok"] = false;
				to_send_string = j.dump();
				send(_fd, to_send_string.c_str(), to_send_string.length(), 0);
			}
			break;
		}
		case OPP_TURN: {
			if (recv_json["ok"] == true) {
				_state = OPP_TURN;
			}
			break;
		}
		case GAME_OVER: {
			if (recv_json["ok"] == true) {
				json j = _server->client_list(this);
				to_send_string = j.dump();
				send(_fd, to_send_string.c_str(),to_send_string.length(), 0);
				_state = INVITE_OR_BE_INVITED;
			}
			break;
		}
	}
}

void Client::set_chess(Chess* chess) {
	_chess = chess;
}