#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>
#include <string>
#include "util.h"
#include "json.hpp"
using json = nlohmann::json;

class Chess;
class Server;

enum ClientState {
	CREATE, // wait for name, return list
	INVITE, // invite others
	BE_INVITED, // be invited
	WAIT_INVATE_REPLY, // wait for invite replay, return ok or not
	OUR_TURN, // wait for our turn and then send to opp
	OPP_TURN, // wait for opp turn and then send to us
};

class Client {
 public:
 	Client(struct sockaddr_in addr, int fd, int idx, Server* server);
 	~Client();
 	int fd();
 	int idx();
 	std::string state_string();
 	std::string name();
 	void transfer(json& recv_json);
 	void set_chess(Chess* chess);
 	bool playing();
 private:
 	void transfer_from_create(json& recv_json);
 	void transfer_from_invite(json& recv_json);
 	void transfer_from_be_invited(json& recv_json);
 	void transfer_from_wait_invate_reply(json& recv_json);
 	void transfer_from_our_turn(json& recv_json);
 	void transfer_from_opp_turn(json& recv_json);
	int _fd;
	int _idx;
	std::string _name;
	Chess* _chess;
	int _opp_fd; // used fd instead of ptr, because ptr may be deleted.
	int _invitor_fd;
	ClientState _state;
	Server* _server;
	struct sockaddr_in _addr;
};

#endif