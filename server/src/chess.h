#ifndef CHESS_H
#define CHESS_H

class Client;

class Chess {
 public:
 	Chess();
 	void set_p1(Client* p1);
 	void set_p2(Client* p2);

 private:
 	Client* _p1;
 	Client* _p2;
};

#endif