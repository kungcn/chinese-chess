#include "chess.h"
#include "client.h"

Chess::Chess(Client* p1, Client* p2)  {
	_p1 = p1;
	_p2 = p2;
	_ref = 2;
	_over = false;
	_winner = NULL;
}

bool Chess::move(Client* p, int before_x, int before_y, int after_x, int after_y) {
	if (!check_inside(before_x, before_y) || !check_inside(after_x, after_y))
		return false;

	PIECE_TYPE t = m[before_x][before_y];
	switch (t) {
		case SHUAI: {
			
			break;
		}
		case SHI: {

			break;
		}
		case XIANG: {

			break;
		}
		case MA: {

			break;
		}
		case CHE: {

			break;
		}
		case PAO: {

			break;
		}
		case BING: {

			break;
		}
		case NONE: {
			return false;
		}
	}
}

Client* Chess::winner() {
	return _winner;
}

bool Chess::game_over() {
	return _over;
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
