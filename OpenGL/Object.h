//
// Created by hao on 4/23/17.
//

#ifndef CG_PROJECT_OBJECT_H
#define CG_PROJECT_OBJECT_H


#include "Defination.h"
#include "Shader.h"

class Object {
public:
    vector<Vertex> vertices;
    vector<Texture> textures;
    Object(vector<Vertex> &vertices, vector<Texture> &texture);
    ~Object();
    void Draw(Shader &shader, Camera &camera, vec3 &lightPos);

private:
    GLuint VAO, VBO;
    void setupMesh();
};


#endif //CG_PROJECT_OBJECT_H
