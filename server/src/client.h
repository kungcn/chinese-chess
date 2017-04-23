#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>
#include <errno.h> 
#include <string>
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