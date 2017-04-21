#include "client.h"

Client::Client(struct sockaddr_in addr, int fd) {
	_addr = addr;
	_fd = fd;
}

int Client::fd() {
	return _fd;
}

int Client::idx() {
	return _idx;
}