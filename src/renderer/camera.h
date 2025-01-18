#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
    glm::vec2 position;   // Camera position
    float zoom;           // Zoom level (default is 1.0f)
    float rotation;       // Rotation in degrees (default is 0.0f)
    glm::vec2 viewportSize; // Screen dimensions in pixels

    Camera()
        : viewportSize(800.0f, 600.0f) {}

    Camera(glm::vec2 viewportSize)
        : position(0.0f, 0.0f), zoom(20.0f), rotation(0.0f), viewportSize(viewportSize) {}

    void setViewportSize(const glm::vec2& newSize);
    void setPosition(const glm::vec2& newPosition);
    void setZoom(float newZoom);
    void setRotation(float newRotation);

    glm::vec2 getViewportSize() const;
    glm::vec2 getPosition() const;
    float getZoom() const;
    float getRotation() const;

    glm::mat4 getProjectionMatrix() const;

    glm::mat4 getViewMatrix() const;

    // Get the combined View-Projection matrix
    glm::mat4 getViewProjectionMatrix() const;
};
