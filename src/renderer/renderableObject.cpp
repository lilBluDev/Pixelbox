#include "RenderableObject.h"

RenderableObject::RenderableObject(const std::vector<float>& vertices)
    : position(0.0f), scale(1.0f), rotationAngle(0.0f), rotationAxis(0.0f, 1.0f, 0.0f), vertices(vertices) {
    updateModelMatrix();
}

void RenderableObject::setPosition(const glm::vec3& pos) {
    position = pos;
    updateModelMatrix();
}

void RenderableObject::setRotation(float angle, const glm::vec3& axis) {
    rotationAngle = angle;
    rotationAxis = axis;
    updateModelMatrix();
}

void RenderableObject::setScale(const glm::vec3& scale) {
    this->scale = scale;
    updateModelMatrix();
}

const glm::mat4& RenderableObject::getModelMatrix() const {
    return modelMatrix;
}

const std::vector<float>& RenderableObject::getVertices() const {
    return vertices;
}

void RenderableObject::updateModelMatrix() {
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationAngle), rotationAxis);
    modelMatrix = glm::scale(modelMatrix, scale);
}
