#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "RenderableObject.h"
#include "renderer/camera.h"

class Renderer {
public:
    Renderer();
    ~Renderer();

    void addObject(RenderableObject* object); // Add renderable object
    void render();                            // Render all objects
    void setShaderProgram(GLuint shaderProgram);
    void renderView(const Camera& camera);

private:
    GLuint VAO, VBO;
    GLuint shaderProgram;

    void setupBuffer(const std::vector<float>& vertices);
};