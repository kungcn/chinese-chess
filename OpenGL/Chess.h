//
// Created by hao on 4/24/17.
//

#ifndef CHINESE_CHESS_CHESS_H
#define CHINESE_CHESS_CHESS_H

#include "Header.h"
#include "Shader.h"
#include "Definition.h"
#include "auxiliary.h"

enum Chess_Type {
    KING = 0,     // 将
    MANDARIN, // 士
    ELEPHANT, // 象
    KNIGHT,   // 马
    ROOK,     // 车
    CANNON,   // 炮
    PAWN      // 兵
};

enum Color_Type {
    RED = 0,
    BLACK
};

class Chess {
public:
    static const Chess_Type chessList[];
    Chess(Color_Type colorType, Chess_Type chessType, unsigned int no);
    bool getState() {
        return alive;
    }
    void dead() {
        alive = false;
    }
    void Draw(GLuint &VAO, const mat4 &model, GLuint &diffuseTex, GLuint &specularTex) {
        drawObject(VAO, model, diffuseTex, specularTex);
    }
    void Draw(Model ourModel, Shader &shader, const mat4 &model) {
        drawModel(ourModel, shader, model);
    }
    unsigned row, col;
private:
    Color_Type colorType;
    Chess_Type chessType;
    bool alive;
};

#endif //CHINESE_CHESS_CHESS_H
