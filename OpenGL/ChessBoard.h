//
// Created by hao on 4/24/17.
//

#ifndef CHINESE_CHESS_CHESSBOARD_H
#define CHINESE_CHESS_CHESSBOARD_H

#include "Header.h"
#include "Definition.h"
#include "Chess.h"

class ChessBoard {
public:
    ChessBoard();
    void Draw(GLuint &VAO, GLuint &diffuseTex, GLuint &specularTex);
    void Draw(Model ourModel, Shader &shader, mat4 &scale);

    vec3 boardPosition[10][9];

private:
    vector<Chess> redChesses;
    vector<Chess> blackChesses;
    void createBoard();
};


#endif //CHINESE_CHESS_CHESSBOARD_H
