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
#include "status.h"
#include "client.h"

class Server {
 public:
	Server(int port);

	Status start();

 private:
 	void listen_port();
 	int cal_client_max_fd();
 	int _port;
 	int _fd;
 	static const int _max_client_size = 50;
 	Client* _client[_max_client_size]; // accepted connection fd 
 	int _cur_client_num; // current connection amount
 	static const int _buf_size = 1024;
 	char _buf[_buf_size];
 	Status _status;
};

#endif