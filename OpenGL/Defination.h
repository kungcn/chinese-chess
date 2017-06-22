//
// Created by hao on 4/22/17.
//

#ifndef CG_PROJECT_DEFINATION_H
#define CG_PROJECT_DEFINATION_H

#include "Header.h"
#include "Camera.h"
#include "Shader.h"

extern int x, y;
// Window Size
extern const GLuint WIDTH;
extern const GLuint HEIGHT;
// Perspective
extern const GLfloat FAR;
extern const GLfloat NEAR;
// Mouse Position
extern double lastX, lastY;
// Path to all kind of shader file
extern const char objVSPath[];
extern const char objFragPath[];
extern const char directFragPath[];
extern const char spotFragPath[];
extern const char pointFragPath[];
extern const char lampVSPath[];
extern const char lampFragPath[];
extern const char skyboxVSPath[];
extern const char skyboxFragPath[];
extern const char modelVSPath[];
extern const char modelFragPath[];
// Path to all picture
extern const char wallPicPath[];
extern const char checkboardPath[];
extern const char containerPicPath[];
extern const char containerSpecularPath[];
extern const vector<string> skyBoxPath;
// Path to all model
extern GLchar modelPath[];
// Main camera
extern Camera camera;
// Key pressed state
extern bool keys[1024];
// Cube demo
extern const GLfloat cube[576];
extern glm::vec3 cubePositions[];
extern glm::vec3 cubeScales[];
// Vertex used in Mesh
struct Vertex {
    // Position
    glm::vec3 Position;
    // Normal
    glm::vec3 Normal;
    // TexCoords
    glm::vec2 TexCoords;
};
// Texture used in Mesh
struct Texture {
    GLuint id;
    string type;
    aiString path;
};

#endif //CG_PROJECT_DEFINATION_H
