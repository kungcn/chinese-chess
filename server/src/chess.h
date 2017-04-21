#ifndef CHESS_H
#define CHESS_H

class Client;

class Chess {
 public:
 	Chess(Client* p1, Client* p2)  {
		_p1 = p1;
		_p2 = p2;
		_ref = 2;
	}
 	int ref();
 	void release();
 private:
 	int _ref;
 	Client* _p1;
 	Client* _p2;
};

#endif