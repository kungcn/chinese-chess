#include <stdio.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <string.h>  
#include <stdlib.h>  
#include <unistd.h>  
  
int main(int argc, char *argv[])  
{  
    if(argc != 2) {  
        printf("Usage: %s <port>\n", argv[0]);  
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
    write(fd,"hello select test!", strlen("hello select test!"));  
    char buf[100] = {0};  
    int nread = read(fd, buf, sizeof(buf));  
    if(nread == 0) {  
        printf("%s\n","server closed!");  
        close(fd);  
    } else {
        printf("%s\n", buf);
    }  
    return 0;  
}  