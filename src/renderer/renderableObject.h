#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class RenderableObject {
public:
    RenderableObject(const std::vector<float>& vertecies);

    void setPosition(const glm::vec3& pos);
    void setRotation(float angle, const glm::vec3& axis);
    void setScale(const glm::vec3& scale);

    const glm::mat4& getModelMatrix() const;
    const std::vector<float>& getVertices() const;

private:
    glm::vec3 position;
    glm::vec3 scale;
    glm::mat4 modelMatrix;

    float rotationAngle;
    glm::vec3 rotationAxis;

    std::vector<float> vertices;

    void updateModelMatrix();
};