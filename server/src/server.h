#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>  
#include <unistd.h>  
#include <sys/select.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <errno.h>  
#include <set>
#include "status.h"
#include "client.h"
#include "chess.h"

class Server {
 public:
	Server(int port);
	Status start();
 	json client_list(Client* client_ptr);
 	Client* find_client_ptr_by_fd(int fd);
 private:
 	void listen_port();
 	int cal_client_max_fd();
 	void accept_client();
 	void process_client(Client* client_ptr);
 	int _port;
 	int _fd;
 	fd_set _fdsr; // used for select
 	static const int _max_client_size = 50;
 	Client* _client[_max_client_size]; // accepted connection fd 
 	int _cur_client_num; // current connection amount
 	static const int _buf_size = 1024;
 	char _buf[_buf_size];
 	std::set<Chess*> _chess_set;
 	Status _status;
};

#endif