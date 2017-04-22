#ifndef CHESS_H
#define CHESS_H

class Client;

enum PIECE_TYPE {
	SHUAI,
	SHI,
	XIANG,
	MA,
	CHE,
	PAO,
	BING,
	NONE
};

class Chess {
 public:
 	Chess(Client* p1, Client* p2);
 	bool move(Client* p, int before_x, int before_y, int after_x, int after_y);
 	Client* winner();
 	bool game_over();
 	void release();
 private:
 	PIECE_TYPE m[10][9];
 	bool check_inside(int x, int y);
 	int _ref;
 	bool _over;
 	Client* _winner;
 	Client* _p1; // player1 first
 	Client* _p2;
};

#endif