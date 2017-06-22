#include "util.h"

int send_json(int fd, json& j) {
	std::string s;
	s = j.dump();
	return send(fd, s.c_str(), s.length(), 0);
}