#include <stdio.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <string.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include "json.hpp"
#include <string>
using json = nlohmann::json;

int main(int argc, char *argv[])  
{  
    if(argc != 3) {  
        printf("Usage: %s <port> <name>\n", argv[0]);  
        exit(1);  
    }  
    int port = atoi(argv[1]);  
    int fd = socket(AF_INET, SOCK_STREAM, 0);  
    struct sockaddr_in socksrv;  
    bzero(&socksrv, sizeof(socksrv));  
    socksrv.sin_family = AF_INET;  
    socksrv.sin_addr.s_addr = htonl(INADDR_ANY);  
    socksrv.sin_port = htons(port);  
    connect(fd, (struct sockaddr*)&socksrv, sizeof(socksrv));  

    json data = {{"name", argv[2]}};
    std::string s = data.dump();
    write(fd, s.c_str(), s.length());
    char buf[100] = {0};
    int nread = read(fd, buf, sizeof(buf));
    buf[nread] = '\0'; 
    if(nread == 0) {  
        printf("%s\n","server closed!");  
    } else {
        printf("%s\n", buf);
    }
    close(fd);  
    return 0;  
}  