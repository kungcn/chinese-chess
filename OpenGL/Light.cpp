//
// Created by hao on 4/23/17.
//

#include "Light.h"

Light* LightHandler::light = nullptr;

const string Light::attribHeader = "pointLights[";
const vector<string> Light::pointAttribs = {
        "].position",
        "].ambient",
        "].diffuse",
        "].specular",
        "].constant",
        "].linear",
        "].quadratic"
};

Light::Light() : shader(objVSPath, multiFragPath){
    dirLightInited = false;
    dirLightEnable = false;
    glUniform1i(glGetUniformLocation(shader.Program, "dirLightEnable"), 0);
    pointLightInited = false;
    pointLightEnable = false;
    glUniform1i(glGetUniformLocation(shader.Program, "pointLightEnable"), 0);
    spotLightInited = false;
    spotLightEnable = false;
    glUniform1i(glGetUniformLocation(shader.Program, "spotLightEnable"), 0);
}
void Light::ChangeDirLight(vec3 direction, vec3 ambient, vec3 diffuse, vec3 specular)
{
    shader.Use();
    dirLightInited = true;
    glUniform1i(glGetUniformLocation(shader.Program, "dirLightEnable"), 0);
    glUniform3f(glGetUniformLocation(shader.Program, "dirLight.direction"), direction.x, direction.y, direction.z);
    glUniform3f(glGetUniformLocation(shader.Program, "dirLight.ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.Program, "dirLight.diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.Program, "dirLight.specular"), specular.x, specular.y, specular.z);
}

void Light::AddPointLight(vec3 position, vec3 ambient,
                          vec3 diffuse, vec3 specular,
                          float constant, float linear, float quadratic)
{
    shader.Use();

    pointLightInited = true;
    glUniform1i(glGetUniformLocation(shader.Program, "pointLightEnable"), 0);
    string no;
    stringstream ss;
    ss << pointPositions.size();
    ss >> no;
//    cout << attribHeader + no + pointAttribs[0] << endl;
    glUniform3f(glGetUniformLocation(shader.Program, (attribHeader + no + pointAttribs[0]).c_str()),
                position.x, position.y, position.z);
    glUniform3f(glGetUniformLocation(shader.Program, (attribHeader + no + pointAttribs[1]).c_str()),
                ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.Program, (attribHeader + no + pointAttribs[2]).c_str()),
                diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.Program, (attribHeader + no + pointAttribs[3]).c_str()),
                specular.x, specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shader.Program, (attribHeader + no + pointAttribs[4]).c_str()), constant);
    glUniform1f(glGetUniformLocation(shader.Program, (attribHeader + no + pointAttribs[5]).c_str()), linear);
    glUniform1f(glGetUniformLocation(shader.Program, (attribHeader + no + pointAttribs[6]).c_str()), quadratic);

    pointPositions.push_back(position);

    glUniform1i(glGetUniformLocation(shader.Program, "pointNums"), (int)pointPositions.size());

}

void Light::ChangeSpotLight(vec3 ambient, vec3 diffuse, vec3 specular,
                            float cutoff, float outerCutOff, float constant,
                            float linear, float quadratic) {
    shader.Use();
    spotLightInited = true;
    glUniform1i(glGetUniformLocation(shader.Program, "spotLightEnable"), 0);
    glUniform3f(glGetUniformLocation(shader.Program, "spotLight.ambient"), ambient.x, ambient.y, ambient.z);
    glUniform3f(glGetUniformLocation(shader.Program, "spotLight.diffuse"), diffuse.x, diffuse.y, diffuse.z);
    glUniform3f(glGetUniformLocation(shader.Program, "spotLight.specular"), specular.x, specular.y, specular.z);
    glUniform1f(glGetUniformLocation(shader.Program, "spotLight.constant"), constant);
    glUniform1f(glGetUniformLocation(shader.Program, "spotLight.linear"), linear);
    glUniform1f(glGetUniformLocation(shader.Program, "spotLight.quadratic"), quadratic);
    glUniform1f(glGetUniformLocation(shader.Program, "spotLight.cutOff"), glm::cos(glm::radians(cutoff)));
    glUniform1f(glGetUniformLocation(shader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(outerCutOff)));
}

void Light::ChangeMaterial(float shininess, GLuint &diffuseTex, GLuint &specularTex) {
    shader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularTex);
    // Set material properties
    glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), shininess);
    glUniform1i(glGetUniformLocation(shader.Program, "material.diffuse"),  0);
    glUniform1i(glGetUniformLocation(shader.Program, "material.specular"), 1);
}

void Light::Use(const mat4 &model) {
    shader.Use();
    glm::mat4 view = CameraHandler::camera->GetViewMatrix();
    glm::mat4 projection = glm::perspective(CameraHandler::camera->Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, NEAR, FAR);
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glUniform3f(glGetUniformLocation(shader.Program, "spotLight.position"), CameraHandler::camera->Position.x, CameraHandler::camera->Position.y, CameraHandler::camera->Position.z);
    glUniform3f(glGetUniformLocation(shader.Program, "spotLight.direction"), CameraHandler::camera->Front.x, CameraHandler::camera->Front.y, CameraHandler::camera->Front.z);
}

void Light::Draw(GLuint &VAO, Shader& shader) {
    if (pointLightEnable) {
        shader.Use();
        mat4 view = CameraHandler::camera->GetViewMatrix();
        mat4 projection = glm::perspective(CameraHandler::camera->Zoom, (float) WIDTH / (float) WIDTH, NEAR, FAR);
        glUniform3f(glGetUniformLocation(shader.Program, "viewPos"), CameraHandler::camera->Position.x,
                    CameraHandler::camera->Position.y, CameraHandler::camera->Position.z);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        // Draw Cube
        mat4 model;
        glBindVertexArray(VAO);
        for (int i = 0; i < pointPositions.size(); i++) {
            model = glm::translate(mat4(), pointPositions[i]);
            model = glm::scale(model, vec3(4, 4, 4));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
    }
}

void Light::Triggle(Light_Type lightType) {
    shader.Use();
    if (lightType == DIRECTIONAL_LIGHT && dirLightInited) {
        if (dirLightEnable)
            glUniform1i(glGetUniformLocation(shader.Program, "dirLightEnable"), 0);
        else
            glUniform1i(glGetUniformLocation(shader.Program, "dirLightEnable"), 1);
        dirLightEnable = !dirLightEnable;
    } else if (lightType == POINT_LIGHT && pointLightInited) {
        if (pointLightEnable)
            glUniform1i(glGetUniformLocation(shader.Program, "pointLightEnable"), 0);
        else
            glUniform1i(glGetUniformLocation(shader.Program, "pointLightEnable"), 1);
        pointLightEnable = !pointLightEnable;
    } else if (lightType == SPOT_LIGHT && spotLightInited) {
        if (spotLightEnable)
            glUniform1i(glGetUniformLocation(shader.Program, "spotLightEnable"), 0);
        else
            glUniform1i(glGetUniformLocation(shader.Program, "spotLightEnable"), 1);
        spotLightEnable = !spotLightEnable;
    }

}