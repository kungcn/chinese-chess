//
// Created by hao on 4/23/17.
//

#include "auxiliary.h"

GLuint loadCubemap(const vector<string> &textures) {
    GLuint textureID;
    glGenTextures(1, &textureID);

    int width, height;
    unsigned char *image;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (GLuint i = 0; i < textures.size(); i++) {
        image = SOIL_load_image(textures[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    return textureID;
}

GLuint loadTexture(const string &texture, Picture_Type type) {

    int width, height;
    unsigned char *image;

    GLuint textureID;
    glGenTextures(1, &textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (type == JPG) {
        image = SOIL_load_image(texture.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    } else if (type == PNG) {
        image = SOIL_load_image(texture.c_str(), &width, &height, 0, SOIL_LOAD_RGBA);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textureID;
}

void drawSkybox(GLuint &VAO, Shader &shader, GLuint &skyboxTex) {
    glDepthMask(GL_FALSE);

    shader.Use();

    mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH/(float)WIDTH, NEAR, FAR);

    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // skybox cube
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shader.Program, "skybox"), 0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthMask(GL_TRUE);
}

void drawObject(GLuint &VAO, Light &light, const mat4 &model,
                GLuint &diffuseTex, GLuint &specularTex) {
    if (light.type == SPOT_LIGHT) {
        drawSpotlight(VAO, light, model, diffuseTex, specularTex);
    } else if (light.type == DIRECTIONAL_LIGHT) {
        drawDirectionallight(VAO, light, model, diffuseTex, specularTex);
    } else if (light.type == POINT_LIGHT) {
        drawPointlight(VAO, light, model, diffuseTex, specularTex);
    }
}

void drawPointlight(GLuint &VAO, Light &light, const mat4 &model,
                    GLuint &diffuseTex, GLuint &specularTex) {
    light.shader.Use();
    GLint viewPosLoc = glGetUniformLocation(light.shader.Program, "viewPos");
    glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
    // Set lights properties
    vec3 temp = light.position;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.position"), temp.x, temp.y, temp.z);
    temp = light.ambient;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.ambient"), temp.x, temp.y, temp.z);
    temp = light.diffuse;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.diffuse"), temp.x, temp.y, temp.z);
    temp = light.specular;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.specular"), temp.x, temp.y, temp.z);
    float tempFloat = light.constant;
    glUniform1f(glGetUniformLocation(light.shader.Program, "light.constant"), tempFloat);
    tempFloat = light.linear;
    glUniform1f(glGetUniformLocation(light.shader.Program, "light.linear"), tempFloat);
    tempFloat = light.quadratic;
    glUniform1f(glGetUniformLocation(light.shader.Program, "light.quadratic"), tempFloat);
    // Set material properties
    // Bind diffuse map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularTex);
    glUniform1f(glGetUniformLocation(light.shader.Program, "material.shininess"), 32.0f);
    glUniform1i(glGetUniformLocation(light.shader.Program, "material.diffuse"), 0);
    glUniform1i(glGetUniformLocation(light.shader.Program, "material.specular"), 1);
    // Create camera transformations
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat) WIDTH / (GLfloat) HEIGHT, NEAR, FAR);
    glUniformMatrix4fv(glGetUniformLocation(light.shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(light.shader.Program, "projection"), 1, GL_FALSE,
                       glm::value_ptr(projection));
    // Draw Cubes
    glUniformMatrix4fv(glGetUniformLocation(light.shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void drawDirectionallight(GLuint &VAO, Light &light, const mat4 &model,
                          GLuint &diffuseTex, GLuint &specularTex) {
    light.shader.Use();
    // Set View Position
    glUniform3f(glGetUniformLocation(light.shader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    // Set Light
    vec3 temp = light.direction;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.direction"), temp.x, temp.y, temp.z);
    temp = light.ambient;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.ambient"),  temp.x, temp.y, temp.z);
    temp = light.diffuse;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.diffuse"),  temp.x, temp.y, temp.z);
    temp = light.diffuse;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.specular"), temp.x, temp.y, temp.z);
    // Bind Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularTex);
    // Set material properties
    glUniform1f(glGetUniformLocation(light.shader.Program, "material.shininess"), 32.0f);
    glUniform1i(glGetUniformLocation(light.shader.Program, "material.diffuse"),  0);
    glUniform1i(glGetUniformLocation(light.shader.Program, "material.specular"), 1);
    // Create camera transformations
    glm::mat4 view = camera.GetViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(light.shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, NEAR, FAR);
    glUniformMatrix4fv(glGetUniformLocation(light.shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // Draw Cubes
    glUniformMatrix4fv(glGetUniformLocation(light.shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void drawSpotlight(GLuint &VAO, Light &light, const mat4 &model,
                   GLuint &diffuseTex, GLuint &specularTex) {
    light.shader.Use();
    // Set View Position
    glUniform3f(glGetUniformLocation(light.shader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);
    // Set Light
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.position"), camera.Position.x, camera.Position.y, camera.Position.z);
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
    float tempFloat = light.cutOff;
    glUniform1f(glGetUniformLocation(light.shader.Program, "light.cutOff"), glm::cos(glm::radians(tempFloat)));
    tempFloat = light.outerCutOff;
    glUniform1f(glGetUniformLocation(light.shader.Program, "light.outerCutOff"), glm::cos(glm::radians(tempFloat)));
    tempFloat = light.constant;
    glUniform1f(glGetUniformLocation(light.shader.Program, "light.constant"),  tempFloat);
    tempFloat = light.linear;
    glUniform1f(glGetUniformLocation(light.shader.Program, "light.linear"),    tempFloat);
    tempFloat = light.quadratic;
    glUniform1f(glGetUniformLocation(light.shader.Program, "light.quadratic"), tempFloat);
    vec3 temp = light.ambient;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.ambient"), temp.x, temp.y, temp.z);
    temp = light.diffuse;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.diffuse"), temp.x, temp.y, temp.z);
    temp = light.specular;
    glUniform3f(glGetUniformLocation(light.shader.Program, "light.specular"), temp.x, temp.y, temp.z);
    // Bind Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTex);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularTex);
    // Set material properties
    glUniform1f(glGetUniformLocation(light.shader.Program, "material.shininess"), 32.0f);
    glUniform1i(glGetUniformLocation(light.shader.Program, "material.diffuse"),  0);
    glUniform1i(glGetUniformLocation(light.shader.Program, "material.specular"), 1);
    // Create camera transformations
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, NEAR, FAR);
    glUniformMatrix4fv(glGetUniformLocation(light.shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(light.shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // Draw Cubes
    glUniformMatrix4fv(glGetUniformLocation(light.shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void drawModel(Model ourModel, Shader &shader, const mat4 &model) {
    shader.Use();
    mat4 view = camera.GetViewMatrix();
    mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH/(float)WIDTH, NEAR, FAR);
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    ourModel.Draw(shader);
}