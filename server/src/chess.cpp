#include "chess.h"
#include "client.h"

Chess::Chess() {
	_p1 = _p2 = NULL;
}

void Chess::set_p1(Client* p1) {
	_p1 = p1;
}

void Chess::set_p2(Client* p2) {
	_p2 = p2;
}