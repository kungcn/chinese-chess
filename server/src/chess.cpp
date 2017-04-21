#include "chess.h"
#include "client.h"

int Chess::ref() {
	return _ref;
}

void Chess::release() {
	_ref--;
}

