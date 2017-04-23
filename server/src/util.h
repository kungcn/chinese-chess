#ifndef UTIL_H
#define UTIL_H

#include <sys/socket.h>  
#include <unistd.h>  
#include <netinet/in.h>  
#include <errno.h> 
#include <string>
#include "json.hpp"
using json = nlohmann::json;

int send_json(int fd, json& j);

#endif