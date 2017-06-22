#include <iostream>
#include "server.h"

int check_arg(int argc, char *argv[]) {  
    if(argc != 2) {  
    	return 8080;
    }  
    return atoi(argv[1]);  
} 

int main(int argc, char *argv[]) {
	int port = check_arg(argc, argv);
	
	Server server(port);
	Status status = server.start();

	if (!status.ok()) {
		std::cout << status.msg() << std::endl;
	}
}