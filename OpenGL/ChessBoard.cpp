//
// Created by hao on 4/24/17.
//

#include "ChessBoard.h"

void ChessBoard::createBoard() {
    float xPos, zPos;
    zPos = -45;
    for (int i = 0; i < 10; i++, zPos += 10) {
        xPos = -40;
        for (int j = 0; j < 9; j++, xPos += 10) {
            boardPosition[i][j] = vec3(xPos, 5.5, zPos);
        }
    }
}


