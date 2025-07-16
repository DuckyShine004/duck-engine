#include "engine/camera/Camera.hpp"

#include "manager/display/DisplayManager.hpp"

#include "logger/LoggerMacros.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace manager::display;

namespace engine::camera {

Camera::Camera() : _position(glm::vec3(0.0f)) {
    this->_lastCursorPosition = glm::vec2(-1.0f, -1.0f);
}

Camera::Camera(glm::vec3 position) : _position(position) {
    this->_lastCursorPosition = glm::vec2(-1.0f, -1.0f);
}

Camera::Camera(float x, float y, float z) : _position(glm::vec3(x, y, z)) {
    this->_lastCursorPosition = glm::vec2(-1.0f, -1.0f);
}

void Camera::updateProjection() {
    float aspectRatio = DisplayManager::getInstance().getAspectRatio();

    float fieldOfView = glm::radians(this->_FIELD_OF_VIEW);

    this->_mvp.projection = glm::perspective(fieldOfView, aspectRatio, this->_NEAR, this->_FAR);
}

void Camera::updateView() {
    this->_viewComponents.front = glm::normalize(this->_rotation.direction);

    this->_viewComponents.right = glm::cross(this->_viewComponents.front, this->_viewComponents.up);

    this->_mvp.view = glm::lookAt(this->_position, this->_position + this->_viewComponents.front, this->_viewComponents.up);
}

void Camera::update() {
}

void Camera::updateModelViewProjection() {
    glm::vec3 camPos = {0, 0, 3};
    glm::vec3 camTarget = {0, 0, 0};
    glm::vec3 up = {0, 1, 0};

    this->_mvp.model = glm::mat4(1.0f);
    this->_mvp.model = glm::translate(this->_mvp.model, glm::vec3(0.0f, -3.0f, -5.0f));
    // this->_mvp.view = glm::lookAt(camPos, camTarget, up);
}

void Camera::uploadModelViewProjection(Shader &shader) {
    shader.setMatrix4fv("uModel", this->_mvp.model);
    shader.setMatrix4fv("uView", this->_mvp.view);
    shader.setMatrix4fv("uProjection", this->_mvp.projection);
}

void Camera::rotate(glm::vec2 cursorPosition) {
    if (this->_lastCursorPosition.x == -1.0f && this->_lastCursorPosition.y == -1.0f) {
        this->_lastCursorPosition = cursorPosition;
    }

    glm::vec2 offset = this->getCursorOffset(cursorPosition);

    this->_lastCursorPosition = cursorPosition;

    this->_rotation.yaw += offset.x;
    this->_rotation.pitch = glm::clamp(this->_rotation.pitch + offset.y, -this->_PITCH_LIMIT, this->_PITCH_LIMIT);

    float theta = glm::radians(this->_rotation.yaw);
    float omega = glm::radians(this->_rotation.pitch);

    this->_rotation.direction.x = glm::cos(theta) * glm::cos(omega);
    this->_rotation.direction.y = glm::sin(omega);
    this->_rotation.direction.z = glm::sin(theta) * glm::cos(omega);
}

glm::vec2 Camera::getCursorOffset(glm::vec2 cursorPosition) {
    float offsetX = (cursorPosition.x - this->_lastCursorPosition.x) * this->_SENSITIVITY;
    float offsetY = (this->_lastCursorPosition.y - cursorPosition.y) * this->_SENSITIVITY;

    return glm::vec2(offsetX, offsetY);
}

glm::mat4 Camera::getProjectionMatrix() {
    return this->_mvp.projection;
}

} // namespace engine::camera