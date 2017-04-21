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

class Server {
 public:
	Server(int port) {
		_port = port;
	}

	Status start();

 private:
 	int _port;
};

#endif