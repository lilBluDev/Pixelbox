#include "renderer/Renderer.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

Renderer::Renderer() {}

Renderer::~Renderer() {}

void Renderer::setShaderProgram(GLuint sp) {
    shaderProgram = sp;
}

void Renderer::addObject(RenderableObject* object) {
    setupBuffer(object->getVertices());
    glUseProgram(shaderProgram);

    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(object->getModelMatrix()));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, object->getVertices().size() / 3);
    glBindVertexArray(0);
}

void Renderer::setupBuffer(const std::vector<float>& vertices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::render() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
}

void Renderer::renderView(const Camera& camera) {
    GLuint viewLoc = glGetUniformLocation(shaderProgram, "u_view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &camera.getViewMatrix()[0][0]);

    GLuint projLoc = glGetUniformLocation(shaderProgram, "u_projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &camera.getProjectionMatrix()[0][0]);
}
