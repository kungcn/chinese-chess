//
// Created by hao on 4/24/17.
//

#include "ChessBoard.h"

ChessBoard::ChessBoard() {
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

void ChessBoard::Draw(GLuint &VAO, GLuint &diffuseTex, GLuint &specularTex) {
    int row, col;
    mat4 model;
    for (int i = 0; i < redChesses.size(); i++) {
        row = redChesses[i].row;
        col = redChesses[i].col;
        if (redChesses[i].getState()) {
            model = translate(mat4(), boardPosition[row][col]);
            model = scale(model, vec3(10, 10, 10));
            redChesses[i].Draw(VAO, model, diffuseTex, specularTex);
        }
    }
    for (int i = 0; i < blackChesses.size(); i++) {
        row = blackChesses[i].row;
        col = blackChesses[i].col;
        if (blackChesses[i].getState()) {
            model = translate(mat4(), boardPosition[row][col]);
            model = scale(model, vec3(10, 10, 10));
            blackChesses[i].Draw(VAO, model, diffuseTex, specularTex);
        }
    }
}
void ChessBoard::Draw(Model ourModel, Shader &shader, mat4 &scale) {
    int row, col;
    mat4 model;
    for (int i = 0; i < redChesses.size(); i++) {
        row = redChesses[i].row;
        col = redChesses[i].col;
        if (redChesses[i].getState()) {
            model = translate(scale, boardPosition[row][col]);
            redChesses[i].Draw(ourModel, shader, model);
        }
    }
    for (int i = 0; i < blackChesses.size(); i++) {
        row = blackChesses[i].row;
        col = blackChesses[i].col;
        if (blackChesses[i].getState()) {
            model = translate(scale, boardPosition[row][col]);
            blackChesses[i].Draw(ourModel, shader, model);
        }
    }
}

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


