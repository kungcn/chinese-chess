#include <iostream>
#include "server.h"

int check_arg(int argc, char *argv[]) {  
    if(argc !=2 ) {  
        printf("Usage: %s <port>\n", argv[0]);  
        return -1;  
    }  
    return atoi(argv[1]);  
} 

int main(int argc, char *argv[]) {
	int port = check_arg(argc, argv);
	if (port == -1) {
		port = 8080;
	}
	
	Server server(port);
	Status status = server.start();

	if (!status.ok()) {
		std::cout << status.msg() << std::endl;
	}
}