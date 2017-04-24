//
// Created by hao on 4/22/17.
//

#ifndef CG_PROJECT_DEFINATION_H
#define CG_PROJECT_DEFINATION_H

#include "Header.h"
#include "Camera.h"
#include "Shader.h"
#include "Light.h"

// Window Size
extern const GLuint WIDTH;
extern const GLuint HEIGHT;
// Perspective
extern const GLfloat FAR;
extern const GLfloat NEAR;
// Mouse Position
extern double lastX, lastY;
// Main camera
extern bool skyboxEnable;
extern bool modelEnable;
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
