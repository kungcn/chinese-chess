//
// Created by hao on 4/24/17.
//

#include "Chess.h"

const Chess_Type Chess::chessList[] = {KING, MANDARIN, ELEPHANT, KNIGHT, ROOK, CANNON, PAWN};

Chess::Chess(Color_Type colorType, Chess_Type chessType, unsigned int no) {
    this->colorType = colorType;
    this->chessType = chessType;
    if (chessType == PAWN) {
        colorType == RED ? row = 6 : row = 3;
        col = no * 2;
    } else if (chessType == CANNON) {
        colorType == RED ? row = 7 : row = 2;
        no == 0 ? col = 1 : col = 7;
    } else {
        colorType == RED ? row = 9 : row = 0;
        col = 4;
        no == 0 ? col -= chessType : col += chessType;
    }
    alive = true;
}