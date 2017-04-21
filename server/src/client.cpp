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
				_chess = new Chess(this, opp_ptr);
				opp_ptr->set_chess(_chess);
				json j;
				if (_fd & 1) {
					j["first"] = false;
					_state = OUR_TURN;
				} else {
					j["first"] = true;
					_state = OPP_TURN;
				}
				to_send_string = j.dump();
				send(_opp_fd, to_send_string.c_str(),to_send_string.length(), 0);
				j["first"] = !j["first"];
				to_send_string = j.dump();
				send(_fd, to_send_string.c_str(),to_send_string.length(), 0);
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

void Client::set_chess(Chess* chess) {
	_chess = chess;
}