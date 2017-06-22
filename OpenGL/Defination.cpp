//
// Created by hao on 4/22/17.
//

#include "Defination.h"

int x = 0, y = 0;

const GLuint WIDTH = 800, HEIGHT = 600;

double lastX = WIDTH / 2, lastY = HEIGHT / 2;

const GLfloat FAR = 1000.0f;
const GLfloat NEAR = 0.1f;

const char objVSPath[] = "Shaders/obj.vs";
const char objFragPath[] = "Shaders/obj.frag";
const char directFragPath[] = "Shaders/directionallight.frag";
const char spotFragPath[] = "Shaders/spotlight.frag";
const char pointFragPath[] = "Shaders/pointlight.frag";
const char lampVSPath[] = "Shaders/lamp.vs";
const char lampFragPath[] = "Shaders/lamp.frag";
const char skyboxVSPath[] = "Shaders/skybox.vs";
const char skyboxFragPath[] = "Shaders/skybox.frag";
const char modelVSPath[] = "Shaders/model.vs";
const char modelFragPath[] = "Shaders/model.frag";
const char checkboardPath[] = "Textures/Objects/timg.png";
const char wallPicPath[] = "Textures/Objects/wall.jpg";

const char containerPicPath[] = "Textures/Objects/container2.png";
const char containerSpecularPath[] = "Textures/Objects/container2_specular.png";

const vector<string> skyBoxPath =  {
        "Textures/SkyBoxs/right.jpg",
        "Textures/SkyBoxs/left.jpg",
        "Textures/SkyBoxs/top.jpg",
        "Textures/SkyBoxs/bottom.jpg",
        "Textures/SkyBoxs/back.jpg",
        "Textures/SkyBoxs/front.jpg"
};

GLchar modelPath[] = "Models/2b/2b.obj";

Camera camera(vec3(0, 10, 3));

bool keys[1024];

const GLfloat cube[576] = {
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f,  1.0f,
        0.5f, 0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3(17.5f, 7.5f, 17.5f),
        glm::vec3(17.5f, 7.5f, -17.5f),
        glm::vec3(-17.5f, 7.5f, 17.5f),
        glm::vec3(-17.5f, 7.5f, -17.5f),

        glm::vec3(30.0f, 5.0f, 24.0f),
        glm::vec3(30.0f, 5.0f, -24.0f),
        glm::vec3(-30.0f, 5.0f, 24.0f),
        glm::vec3(-30.0f, 5.0f, -24.0f),

        glm::vec3(-40.0f, 5.0f, 0.0f),
        glm::vec3(40.0f,  5.0f, 0.0f),
        glm::vec3(0.0f,  5.0f, 40.0f),
        glm::vec3(0.0f,  5.0f, -40.0f)
};

glm::vec3 cubeScales[] = {
        glm::vec3(15.0f,  15.0f, 15.0f),
        glm::vec3(15.0f,  15.0f, 15.0f),
        glm::vec3(15.0f,  15.0f, 15.0f),
        glm::vec3(15.0f,  15.0f, 15.0f),

        glm::vec3(10.0f,  10.0f, 2.0f),
        glm::vec3(10.0f,  10.0f, 2.0f),
        glm::vec3(10.0f,  10.0f, 2.0f),
        glm::vec3(10.0f,  10.0f, 2.0f),

        glm::vec3(10.0f,  10.0f, 2.0f),
        glm::vec3(10.0f,  10.0f, 2.0f),
        glm::vec3(2.0f,  10.0f, 10.0f),
        glm::vec3(2.0f,  10.0f, 10.0f)
};