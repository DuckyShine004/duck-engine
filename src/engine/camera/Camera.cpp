#include "engine/camera/Camera.hpp"

#include "manager/display/DisplayManager.hpp"

#include "logger/LoggerMacros.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace manager::display;

namespace engine::camera {

Camera::Camera() : _position(glm::vec3(0.0f)) {
    // glm::mat4 model = glm::mat4(1.0f);
    // model = glm::scale(model, glm::vec3(20.0f, 20.0f, 20.0f));
    // this->_mvp.model = model;
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
    this->_mvp.view = glm::lookAt(this->_position, this->_position + this->_viewComponents.front, this->_viewComponents.up);
}

void Camera::update(GLFWwindow *window, float deltaTime) {
    this->_mvp.model = glm::rotate(this->_mvp.model, glm::radians(50.0f) * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f));

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        this->move(FORWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        this->move(BACKWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        this->move(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        this->move(LEFT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        this->move(UP, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        this->move(DOWN, deltaTime);
    }
}

void Camera::uploadViewProjection(Shader &shader) {
    shader.setMatrix4fv("uView", this->_mvp.view);
    shader.setMatrix4fv("uProjection", this->_mvp.projection);
}

void Camera::uploadModelViewProjection(Shader &shader) {
    shader.setMatrix4fv("uModel", this->_mvp.model);
    shader.setMatrix4fv("uView", this->_mvp.view);
    shader.setMatrix4fv("uProjection", this->_mvp.projection);
}

void Camera::move(Direction direction, float deltaTime) {
    float velocity = this->_SPEED * deltaTime;

    if (direction == FORWARD) {
        this->_position += this->_viewComponents.front * velocity;
    }

    if (direction == BACKWARD) {
        this->_position -= this->_viewComponents.front * velocity;
    }

    if (direction == LEFT) {
        this->_position -= this->_viewComponents.right * velocity;
    }

    if (direction == RIGHT) {
        this->_position += this->_viewComponents.right * velocity;
    }

    if (direction == UP) {
        this->_position += this->_viewComponents.up * velocity;
    }

    if (direction == DOWN) {
        this->_position -= this->_viewComponents.up * velocity;
    }

    this->updateView();
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

    this->_viewComponents.front = glm::normalize(this->_rotation.direction);
    this->_viewComponents.right = glm::cross(this->_viewComponents.front, this->_viewComponents.up);
}

glm::vec2 Camera::getCursorOffset(glm::vec2 cursorPosition) {
    float offsetX = (cursorPosition.x - this->_lastCursorPosition.x) * this->_SENSITIVITY;
    float offsetY = (this->_lastCursorPosition.y - cursorPosition.y) * this->_SENSITIVITY;

    return glm::vec2(offsetX, offsetY);
}

glm::mat4 Camera::getProjectionMatrix() {
    return this->_mvp.projection;
}

glm::vec3 Camera::getPosition() {
    return this->_position;
}

} // namespace engine::camera