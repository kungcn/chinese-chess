#ifndef CLIENT_H
#define CLIENT_H

#include <sys/socket.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <errno.h> 

class Client {
 public:
 	Client(struct sockaddr_in addr, int fd);
 	int fd();
 	int idx();
 private:
	int _fd;
	int _idx;
	struct sockaddr_in _addr;
};

#endif