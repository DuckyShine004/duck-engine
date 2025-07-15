#include "engine/camera/Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace engine::camera {

Camera::Camera() : _projectionMatrix(glm::mat4(1.0f)) {
}

void Camera::updateAspectRatio(int width, int height) {
    this->_projectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
}

glm::mat4 Camera::getProjectionMatrix() {
    return this->_projectionMatrix;
}

} // namespace engine::camera