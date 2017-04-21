#include "client.h"
#include "chess.h"
#include "server.h"
Client::Client(struct sockaddr_in addr, int fd, Server* server) {
	_addr = addr;
	_fd = fd;
	_name = "empty";
	_chess = NULL;
	_server = server;
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
	switch(_state) { // todo catch error
		case CREATE: {
			_name = recv_json["name"];
			json j = _server->client_list(this);
			std::string to_send_string = j.dump();
			send(_fd, to_send_string.c_str(),to_send_string.length(), 0);
			_state = INVITE_OR_BE_INVITED;
			break;
		}
		case INVITE_OR_BE_INVITED: {
			break;
		}
		case WAIT_INVATE_REPLY: {
			break;
		}
		case OUR_TURN: {
			break;
		}
		case OPP_TURN: {
			break;
		}
		case GAME_OVER: {
			break;
		}
	}
}