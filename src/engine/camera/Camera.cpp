#include "engine/camera/Camera.hpp"

#include "manager/display/DisplayManager.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace manager::display;

namespace engine::camera {

Camera::Camera() = default;

Camera::Camera(glm::vec3 position) : _position(position) {
}

Camera::Camera(float x, float y, float z) : Camera(glm::vec3(x, y, z)) {
}

void Camera::updateAspectRatio() {
    float aspectRatio = DisplayManager::getInstance().getAspectRatio();

    float fieldOfView = glm::radians(this->_FIELD_OF_VIEW);

    this->_mvp.projection = glm::perspective(fieldOfView, 1280.0f / 720.0f, this->_NEAR, this->_FAR);
}

void Camera::update() {
    this->updateModelViewProjectionMatrices();
}

void Camera::updateModelViewProjectionMatrices() {
}

void Camera::uploadModelViewProjectionMatrices(Shader &shader) {
    shader.setMatrix4fv("uModel", this->_mvp.model);
    shader.setMatrix4fv("uView", this->_mvp.view);
    shader.setMatrix4fv("uProjection", this->_mvp.projection);
}

glm::mat4 Camera::getProjectionMatrix() {
    return this->_mvp.projection;
}

} // namespace engine::camera