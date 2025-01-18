#include "renderer/camera.h"

#include <iostream>

void Camera::setViewportSize(const glm::vec2& newSize) {
    viewportSize = newSize;
}

void Camera::setPosition(const glm::vec2& newPosition) {
    position = newPosition;
}

void Camera::setZoom(float newZoom) {
    zoom = newZoom;
}

void Camera::setRotation(float newRotation) {
    rotation = newRotation;
}

glm::vec2 Camera::getViewportSize() const {
    return viewportSize;
}

glm::vec2 Camera::getPosition() const {
    return position;
}

float Camera::getZoom() const {
    return zoom;
}

float Camera::getRotation() const {
    return rotation;
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::ortho(
        0.0f, viewportSize.x,    // Left, Right
        viewportSize.y, 0.0f,    // Bottom, Top (invert Y for SDL coordinates)
        -1.0f, 1.0f              // Near, Far
    );
}

glm::mat4 Camera::getViewMatrix() const {
    glm::mat4 view = glm::mat4(1.0f); 
    
    view = glm::translate(view, glm::vec3(-position, 0.0f));
    view = glm::rotate(view, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    view = glm::scale(view, glm::vec3(zoom, zoom, 1.0f));

    return view;
}

glm::mat4 Camera::getViewProjectionMatrix() const {
    return getProjectionMatrix() * getViewMatrix();
}