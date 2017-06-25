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
	_state = CREATE;
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
		send_json(opp->fd(), j);
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
	if (recv_json["get_list"] == true) {
		json j = _server->client_list(this);
		send_json(_fd, j);
		return;
	}

	switch(_state) { // todo catch error
		case CREATE:
			transfer_from_create(recv_json);
			break;
		case INVITE:
			transfer_from_invite(recv_json);
			break;
		case BE_INVITED:
			transfer_from_be_invited(recv_json);
			break;
		case WAIT_INVATE_REPLY:
			transfer_from_wait_invate_reply(recv_json);
			break;
		case OUR_TURN:
			transfer_from_our_turn(recv_json);
			break;
		case OPP_TURN:
			transfer_from_opp_turn(recv_json);
			break;
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


void Client::transfer_from_create(json& recv_json) {
	if (recv_json["name"] != nullptr) {
		_name = recv_json["name"];
		json j = _server->client_list(this);
		send_json(_fd, j);
		_state = INVITE;
	}
}

void Client::transfer_from_invite(json& recv_json) {
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
		send_json(_opp_fd, j);
	}
}

void Client::transfer_from_be_invited(json& recv_json) {
	if (recv_json["accept"] == true) {
	 	if (recv_json["recv_from_fd"] != _invitor_fd) {
	 		_invitor_fd = -1;
	 		_state = INVITE;
	 		json j;
	 		j["cancel"] = true;
	 		send_json(_fd, j);
	 	}
		_opp_fd = recv_json["recv_from_fd"];
		_invitor_fd = -1;
		Client* opp_ptr = _server->find_client_ptr_by_fd(_opp_fd);
		if (opp_ptr == NULL) {
			_state = INVITE;
			json j;
			j["cancel"] = true;
			send_json(_opp_fd, j);
			return;
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
		send_json(_fd, j);
		j["first"] = !j["first"];
		send_json(_opp_fd, j);
	} else if (recv_json["accept"] == false) {
		_state = INVITE;
		Client* opp_ptr = _server->find_client_ptr_by_fd(_invitor_fd);
		opp_ptr->_state = INVITE;
		json j;
		j["accept"] = false;
		send_json(_invitor_fd, j);
		_invitor_fd = -1;
	}
}

void Client::transfer_from_wait_invate_reply(json& recv_json) {
	if (recv_json["cancel"] == true) {
		Client* opp_ptr = _server->find_client_ptr_by_fd(_opp_fd);
		if (opp_ptr != NULL) {
			opp_ptr->_invitor_fd = -1;
			opp_ptr->_state = INVITE;
			json j;
			j["cancel"] = true;
			send_json(_opp_fd, j);
		}
		_opp_fd = -1;
		_state = INVITE;
	}
}

void Client::transfer_from_our_turn(json& recv_json) {
	bool ok = _chess->move(this, 
	   			 recv_json["before_x"], 
			     recv_json["before_y"],
				 recv_json["after_x"],
			     recv_json["after_y"]);
	json j;
	if (ok) {
		if (!_chess->game_over()) {
			j["ok"] = true;
			send_json(_fd, j);
			send_json(_opp_fd, recv_json);
			_state = OPP_TURN;
		} else { // game over
			if (this == _chess->winner()) {
				j["win"] = true;
				send_json(_fd, j);
				j["win"] = false;
				send_json(_opp_fd, j);
			} else {
				j["win"] = false;
				send_json(_fd, j);
				j["win"] = true;
				send_json(_opp_fd, j);
			}
			Client* opp = _server->find_client_ptr_by_fd(_opp_fd);
			opp->_state = INVITE;
			_state = INVITE;
		}
	} else {
		j["ok"] = false;
		send_json(_fd, j);
	}
}

void Client::transfer_from_opp_turn(json& recv_json) {
	if (recv_json["ok"] == true && _chess->whose_turn() == this) {
		_state = OUR_TURN;
	}
}
