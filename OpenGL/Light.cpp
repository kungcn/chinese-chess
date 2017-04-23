//
// Created by hao on 4/23/17.
//

#include "Light.h"

void Light::Draw(GLuint &VAO, Shader& shader) {
    shader.Use();
    mat4 view = camera.GetViewMatrix();
    mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH/(float)WIDTH, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    // Draw Cube
    mat4 model = glm::mat4();
    model = glm::translate(model, position);
    model = glm::scale(model, vec3(4, 4, 4));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}