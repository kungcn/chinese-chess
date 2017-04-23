//
// Created by hao on 4/24/17.
//

#ifndef CHINESE_CHESS_CHESSBOARD_H
#define CHINESE_CHESS_CHESSBOARD_H

#include "Header.h"
#include "Defination.h"
#include "Chess.h"

class ChessBoard {
public:
    ChessBoard() {
        createBoard();
        // Fill Red Chess
        blackChesses.push_back(Chess(RED, KING, 0));
        for (int i = 1; i <= CANNON; i = i + 1) {
            blackChesses.push_back(Chess(RED, Chess::chessList[i], 0));
            blackChesses.push_back(Chess(RED, Chess::chessList[i], 1));
        }
        for (int i = 0; i < 5; i++) {
            blackChesses.push_back(Chess(RED, PAWN, i));
        }
        // Fill Black Chess
        blackChesses.push_back(Chess(BLACK, KING, 0));
        for (int i = 1; i <= CANNON; i = i + 1) {
            blackChesses.push_back(Chess(BLACK, Chess::chessList[i], 0));
            blackChesses.push_back(Chess(BLACK, Chess::chessList[i], 1));
        }
        for (int i = 0; i < 5; i++) {
            blackChesses.push_back(Chess(BLACK, PAWN, i));
        }
    }
    vec3 boardPosition[10][9];
    void Draw(GLuint &VAO, Light &light, GLuint &diffuseTex, GLuint &specularTex) {
        int row, col;
        mat4 model;
        for (int i = 0; i < redChesses.size(); i++) {
            row = redChesses[i].row;
            col = redChesses[i].col;

            if (redChesses[i].getState()) {
                model = translate(mat4(), boardPosition[row][col]);
                model = scale(model, vec3(10, 10, 10));
                redChesses[i].Draw(VAO, light, model, diffuseTex, specularTex);
            }
        }
        for (int i = 0; i < blackChesses.size(); i++) {
            row = blackChesses[i].row;
            col = blackChesses[i].col;
            if (blackChesses[i].getState()) {
                model = translate(mat4(), boardPosition[row][col]);
                model = scale(model, vec3(10, 10, 10));
                redChesses[i].Draw(VAO, light, model, diffuseTex, specularTex);
            }
        }
    }
private:
    vector<Chess> redChesses;
    vector<Chess> blackChesses;
    void createBoard();
};


#endif //CHINESE_CHESS_CHESSBOARD_H
