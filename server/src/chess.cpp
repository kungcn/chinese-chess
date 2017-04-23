#include "chess.h"
#include "client.h"
#include <cmath>

Chess::Chess(Client* p1, Client* p2)  {
	_p1 = p1;
	_p2 = p2;
	_ref = 2;
	_over = false;
	_winner = NULL;
	this->init_m();
}

void Chess::init_m() {
	m[0][0] = m[0][8] = CHE_2;
	m[9][0] = m[9][8] = CHE_1;
	m[0][1] = m[0][7] = MA_2;
	m[9][1] = m[9][8] = MA_1;
	m[0][2] = m[0][6] = MA_2;
	m[9][2] = m[9][7] = XIANG_1;
	m[0][3] = m[0][5] = MA_2;
	m[9][3] = m[9][6] = SHI_1;
	m[0][4] = SHUAI_2;
	m[9][4] = SHUAI_1;
	m[2][1] = m[2][7] = PAO_2;
	m[7][1] = m[7][7] = PAO_1;
	m[3][0] = m[3][2] = m[3][4] = m[3][6] = m[3][8] = BING_2;
	m[6][0] = m[6][2] = m[6][4] = m[6][6] = m[6][8] = BING_1;
}

bool Chess::move(Client* p, int before_x, int before_y, int after_x, int after_y) {
	bool ok = false;
	if (!check_inside(before_x, before_y) || !check_inside(after_x, after_y))
		return false;
	if (before_x == after_x && before_y && after_y)
		return false;

	PIECE_TYPE t = m[before_x][before_y];
	if (p == _p1) {
		if (type(m[after_x][after_y]) == TYPE_1) return false;
		switch (t) {
			case SHUAI_1:
				ok = shuai1_move(before_x, before_y, after_x, after_y);
				break;
			case SHI_1:
				ok = shi1_move(before_x, before_y, after_x, after_y);
				break;
			case XIANG_1:
				ok = xiang1_move(before_x, before_y, after_x, after_y);
				break;
			case MA_1:
				ok = ma_move(before_x, before_y, after_x, after_y);
				break;
			case CHE_1:
				ok = che_move(before_x, before_y, after_x, after_y);
				break;
			case PAO_1:
				ok = pao_move(before_x, before_y, after_x, after_y);
				break;
			case BING_1:
				ok = bing1_move(before_x, before_y, after_x, after_y);
				break;
		}
	} else {
		if (type(m[after_x][after_y]) == TYPE_2) return false;
		switch (t) {
			case SHUAI_2:
				ok = shuai2_move(before_x, before_y, after_x, after_y);
				break;
			case SHI_2:
				ok = shi2_move(before_x, before_y, after_x, after_y);
				break;
			case XIANG_2:
				ok = xiang2_move(before_x, before_y, after_x, after_y);
				break;
			case MA_2:
				ok = ma_move(before_x, before_y, after_x, after_y);
				break;
			case CHE_2:
				ok = che_move(before_x, before_y, after_x, after_y);
				break;
			case PAO_2:
				ok = pao_move(before_x, before_y, after_x, after_y);
				break;
			case BING_2:
				ok = bing2_move(before_x, before_y, after_x, after_y);
				break;
		}
	}
	if (ok) {
		m[after_x][after_y] = m[before_x][before_y];
		m[before_x][before_y] = NONE;
		check_game_over();
	}
	return ok;
}

void Chess::check_game_over() {

}

Client* Chess::winner() {
	return _winner;
}

bool Chess::game_over() {
	return _over;
}

PIECE_TYPE Chess::type(PIECE_TYPE t) {
	switch (t) {
		case SHUAI_1:
		case SHI_1:
		case XIANG_1:
		case MA_1:
		case CHE_1:
		case PAO_1:
		case BING_1:
		case TYPE_1:
			return TYPE_1;
		case SHUAI_2:
		case SHI_2:
		case XIANG_2:
		case MA_2:
		case CHE_2:
		case PAO_2:
		case BING_2:
		case TYPE_2:
			return TYPE_2;
		case NONE:
			return NONE;
	}
}

void Chess::release() {
	_ref--;
	if (_ref == 0) {
		delete this;
	}
}

bool Chess::check_inside(int x, int y) {
	return x >= 0 && x < 10 && y >= 0 && y < 9;
}

bool Chess::check_inside_shuai1(int x, int y) {
	return x >= 7 && x <= 9 && y >= 3 && y <= 5;
}
bool Chess::check_inside_shuai2(int x, int y) {
	return x >= 0 && x <= 2 && y >= 3 && y <= 5;
}


bool Chess::check_inside_shi1(int x, int y) {
	return 	(x == 7 && y == 3) ||
			(x == 7 && y == 5) ||
			(x == 8 && y == 4) ||
			(x == 9 && y == 3) ||
			(x == 9 && y == 5);
}
bool Chess::check_inside_shi2(int x, int y) {
	return 	(x == 0 && y == 3) ||
			(x == 0 && y == 5) ||
			(x == 1 && y == 4) ||
			(x == 2 && y == 3) ||
			(x == 2 && y == 5);
}

bool Chess::check_inside_xiang1(int x, int y) {
	return 	(x == 5 && y == 2) ||
			(x == 5 && y == 7) ||
			(x == 7 && y == 4) ||
			(x == 9 && y == 2) ||
			(x == 9 && y == 7);
}
bool Chess::check_inside_xiang2(int x, int y) {
	return 	(x == 4 && y == 2) ||
			(x == 4 && y == 7) ||
			(x == 2 && y == 4) ||
			(x == 0 && y == 2) ||
			(x == 0 && y == 7);
}

bool Chess::shuai1_move(int before_x, int before_y, int after_x, int after_y) {
	if (!check_inside_shuai1(before_x, before_y) || 
		!check_inside_shuai1(after_x, after_y)) return false;

	return abs(after_x - before_x) + abs(after_y - before_y) == 1;
}

bool Chess::shi1_move(int before_x, int before_y, int after_x, int after_y) {
	if (!check_inside_shi1(before_x, before_y) || 
		!check_inside_shi1(after_x, after_y)) return false;

	return abs(after_x - before_x) == 1 && abs(after_y - before_y) == 1;
}
bool Chess::xiang1_move(int before_x, int before_y, int after_x, int after_y) {
	if (!check_inside_xiang1(before_x, before_y) || 
		!check_inside_xiang1(after_x, after_y)) return false;

	return abs(after_x - before_x) == 2 && abs(after_y - before_y) == 2 &&
		   m[(before_x+after_x)/2][(before_y+after_y)/2] == NONE;
}

bool Chess::bing1_move(int before_x, int before_y, int after_x, int after_y) {
	if (abs(after_x - before_x) + abs(after_y - before_y) != 1)
		return false;
	if (before_x >= 5) // only can move up
		return after_x == before_x - 1;
	else
		return after_x != before_x + 1;
}

bool Chess::ma_move(int before_x, int before_y, int after_x, int after_y) {
	if (after_x - before_x == 2 &&
		after_y - before_y == 1 &&
		m[before_x+1][before_y] == NONE)
		return true;
	if (after_x - before_x == 2 &&
		after_y - before_y == -1 &&
		m[before_x+1][before_y] == NONE)
		return true;
	if (after_x - before_x == -2 &&
		after_y - before_y == 1 &&
		m[before_x-1][before_y] == NONE)
		return true;
	if (after_x - before_x == -2 &&
		after_y - before_y == -1 &&
		m[before_x-1][before_y] == NONE)
		return true;
	if (after_x - before_x == 1 &&
		after_y - before_y == 2 &&
		m[before_x][before_y+1] == NONE)
		return true;
	if (after_x - before_x == -1 &&
		after_y - before_y == 2 &&
		m[before_x][before_y+1] == NONE)
		return true;
	if (after_x - before_x == 1 &&
		after_y - before_y == -2 &&
		m[before_x][before_y-1] == NONE)
		return true;
	if (after_x - before_x == -1 &&
		after_y - before_y == -2 &&
		m[before_x][before_y-1] == NONE)
		return true;
	return false;
}
bool Chess::che_move(int before_x, int before_y, int after_x, int after_y) {
	if (after_x - before_x != 0 && after_y - before_y != 0) 
		return false;
	int dx_unit = after_x - before_x > 0 ? 1 : -1;
	int dy_unit = after_y - before_y > 0 ? 1 : -1;
	for (int i = before_x+1; i < after_x; i += dx_unit)
		if (m[i][before_y] != NONE) 
			return false;
	for (int i = before_y+1; i < after_y; i += dy_unit)
		if (m[before_x][i] != NONE) 
			return false;
	return true;
}
bool Chess::pao_move(int before_x, int before_y, int after_x, int after_y) {
	if (after_x - before_x != 0 && after_y - before_y != 0) 
		return false;
	int dx_unit = after_x - before_x > 0 ? 1 : -1;
	int dy_unit = after_y - before_y > 0 ? 1 : -1;
	int mid_cnt = 0;
	for (int i = before_x+1; i < after_x; i += dx_unit)
		if (m[i][before_y] != NONE)
			mid_cnt++;

	for (int i = before_y+1; i < after_y; i += dy_unit)
		if (m[before_x][i] != NONE)
			mid_cnt++;
	return mid_cnt == 1;
}

bool Chess::shuai2_move(int before_x, int before_y, int after_x, int after_y) {
	if (!check_inside_shuai2(before_x, before_y) || 
		!check_inside_shuai2(after_x, after_y)) return false;

	return abs(after_x - before_x) + abs(after_y - before_y) == 1;
}
bool Chess::shi2_move(int before_x, int before_y, int after_x, int after_y) {
	if (!check_inside_shi2(before_x, before_y) || 
		!check_inside_shi2(after_x, after_y)) return false;

	return abs(after_x - before_x) == 1 && abs(after_y - before_y) == 1;
}
bool Chess::xiang2_move(int before_x, int before_y, int after_x, int after_y) {
	if (!check_inside_xiang2(before_x, before_y) || 
		!check_inside_xiang2(after_x, after_y)) return false;

	return abs(after_x - before_x) == 2 && abs(after_y - before_y) == 2 &&
		   m[(before_x+after_x)/2][(before_y+after_y)/2] == NONE;
}

bool Chess::bing2_move(int before_x, int before_y, int after_x, int after_y) {
	if (abs(after_x - before_x) + abs(after_y - before_y) != 1)
		return false;
	if (before_x <= 4) // only can move up
		return after_x == before_x + 1;
	else
		return after_x != before_x - 1;
}