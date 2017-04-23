#ifndef CHESS_H
#define CHESS_H

class Client;

enum PIECE_TYPE {
	SHUAI_1,
	SHI_1,
	XIANG_1,
	MA_1,
	CHE_1,
	PAO_1,
	BING_1,
	SHUAI_2,
	SHI_2,
	XIANG_2,
	MA_2,
	CHE_2,
	PAO_2,
	BING_2,
	TYPE_1,
	TYPE_2,
	NONE
};

class Chess {
 public:
 	Chess(Client* p1, Client* p2);
 	void init_m();
 	bool move(Client* p, int before_x, int before_y, int after_x, int after_y);
 	Client* winner();
 	bool game_over();
 	void release();
 private:
 	void check_game_over();
 	PIECE_TYPE type(PIECE_TYPE t);
 	bool shuai1_move(int before_x, int before_y, int after_x, int after_y);
	bool shi1_move(int before_x, int before_y, int after_x, int after_y);
	bool xiang1_move(int before_x, int before_y, int after_x, int after_y);
	bool ma_move(int before_x, int before_y, int after_x, int after_y);
	bool che_move(int before_x, int before_y, int after_x, int after_y);
	bool pao_move(int before_x, int before_y, int after_x, int after_y);
	bool bing1_move(int before_x, int before_y, int after_x, int after_y);
	bool shuai2_move(int before_x, int before_y, int after_x, int after_y);
	bool shi2_move(int before_x, int before_y, int after_x, int after_y);
	bool xiang2_move(int before_x, int before_y, int after_x, int after_y);
	bool bing2_move(int before_x, int before_y, int after_x, int after_y);
	bool check_inside_shuai1(int x, int y);
	bool check_inside_shuai2(int x, int y);
	bool check_inside_shi1(int x, int y);
	bool check_inside_shi2(int x, int y);
	bool check_inside_xiang1(int x, int y);
	bool check_inside_xiang2(int x, int y);

 	PIECE_TYPE m[10][9];
 	bool check_inside(int x, int y);
 	int _ref;
 	bool _over;
 	Client* _winner;
 	Client* _p1; // player1 first
 	Client* _p2;
};

#endif