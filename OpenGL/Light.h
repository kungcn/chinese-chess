//
// Created by hao on 4/23/17.
//

#ifndef CG_PROJECT_LIGHT_H
#define CG_PROJECT_LIGHT_H

#include "Header.h"
#include "Shader.h"
#include "Defination.h"

enum Light_Type {
    POINT_LIGHT,
    DIRECTIONAL_LIGHT,
    SPOT_LIGHT
};

class Light {
public:
    Light(vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular)
            : shader(objVSPath, directFragPath) {
        this->direction = direction;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        type = DIRECTIONAL_LIGHT;
    }
    Light(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular, float constant, float linear, float quadratic)
            : shader(objVSPath, pointFragPath) {
        this->direction = direction;
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->position = position;
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
        type = POINT_LIGHT;
    }
    Light(vec3 ambient, vec3 diffuse, vec3 specular, float cutoff, float outerCutOff, float constant, float linear, float quadratic)
            : shader(objVSPath, spotFragPath) {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->constant = constant;
        this->linear = linear;
        this->quadratic = quadratic;
        this->cutOff = cutoff;
        this->outerCutOff = outerCutOff;
        type = SPOT_LIGHT;
    }
    void Draw(GLuint &VAO, Shader& shader);

    Shader shader;
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutOff, outerCutOff, constant, linear, quadratic;
    Light_Type type;
};


#endif //CG_PROJECT_LIGHT_H
