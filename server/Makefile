SRCS  = src/main.cpp
SRCS += src/server.cpp

OBJS=$(SRCS:.cpp=.o)

CXX?=g++
CPPFLAGS =-w -Wall -std=c++11 -fpermissive
# CPPFLAGS +=-D DEBUG

all: $(OBJS)
	$(CXX) -o bin/main $(OBJS)  -lm

server.o: src/status.h src/server.h src/server.cpp

main.o: server.o

client: 
	g++ src/simple-client.cpp -o bin/simple-client

clean:
	-rm -f $(OBJS)
	-rm -f bin/main bin/simple-client
