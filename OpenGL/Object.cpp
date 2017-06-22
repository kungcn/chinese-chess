//
// Created by hao on 4/23/17.
//

#include "Object.h"

Object::Object(vector<Vertex> &vertices, vector<Texture> &texture) {
    this->vertices = vertices;
    this->textures = textures;
    this->setupMesh();
}

Object::~Object() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Object::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    // Vertex Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    // Vertex Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    // Vertex Texture Coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

void Object::Draw(Shader &shader, Camera &camera, vec3 &lightPos) {

    shader.Use();

    mat4 projection, view, model;

    GLint viewPosLoc     = glGetUniformLocation(shader.Program, "viewPos");
    glUniform3f(viewPosLoc,     camera.Position.x, camera.Position.y, camera.Position.z);

    glm::vec3 lightColor;
    lightColor.x = sin(glfwGetTime() * 2.0f);
    lightColor.y = sin(glfwGetTime() * 0.7f);
    lightColor.z = sin(glfwGetTime() * 1.3f);

    glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // Decrease the influence
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // Low influence
    // Set lights properties
    glUniform3f(glGetUniformLocation(shader.Program, "light.ambient"),  ambientColor.x, ambientColor.y, ambientColor.z);
    glUniform3f(glGetUniformLocation(shader.Program, "light.diffuse"),  diffuseColor.x, diffuseColor.y, diffuseColor.z);
    glUniform3f(glGetUniformLocation(shader.Program, "light.position"), lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(glGetUniformLocation(shader.Program, "light.specular"), 1.0f, 1.0f, 1.0f);
    // Set material properties
    glUniform3f(glGetUniformLocation(shader.Program, "material.ambient"),   1.0f, 0.5f, 0.31f);
    glUniform3f(glGetUniformLocation(shader.Program, "material.diffuse"),   1.0f, 0.5f, 0.31f);
    glUniform3f(glGetUniformLocation(shader.Program, "material.specular"),  0.5f, 0.5f, 0.5f);
    glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), 32.0f);

    // Create camera transformations
    view = camera.GetViewMatrix();
    projection = glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
    // Get the uniform locations
    GLint modelLoc = glGetUniformLocation(shader.Program, "model");
    GLint viewLoc  = glGetUniformLocation(shader.Program,  "view");
    GLint projLoc  = glGetUniformLocation(shader.Program,  "projection");
    // Pass the matrices to the shader
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glBindVertexArray(VAO);
    for(GLuint i = 0; i < 12; i++)
    {
        // Calculate the model matrix for each object and pass it to shader before drawing
        model = glm::mat4();
        model = glm::translate(model, cubePositions[i]);
        model = glm::scale(model, cubeScales[i]);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    glBindVertexArray(0);
}
