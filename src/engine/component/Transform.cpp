#include "engine/component/Transform.hpp"

namespace engine::component {

// Explicit default initialisation to be safe
Transform::Transform() : _position(0.0f), _rotation(0.0f, 0.0f, 0.0f), _scale(0.0f) {
}

Transform::Transform(glm::vec3 position) : _position(position), _rotation(0.0f, 0.0f, 0.0f), _scale(0.0f) {
}

Transform::Transform(glm::vec3 position, Quaternion rotation) : _position(position), _rotation(rotation), _scale(0.0f) {
}

Transform::Transform(glm::vec3 position, Quaternion rotation, glm::vec3 scale) : _position(position), _rotation(rotation), _scale(scale) {
}

glm::vec3 Transform::getPosition() {
    return this->_position;
}
void Transform::setPosition(glm::vec3 position) {
    this->_position = position;
}

Quaternion Transform::getRotation() {
    return this->_rotation;
}

void Transform::setRotation(Quaternion quaternion) {
    this->_rotation = quaternion;
}

glm::vec3 Transform::getScale() {
    return this->_scale;
}

void Transform::setScale(glm::vec3 scale) {
    this->_scale = scale;
}

void Transform::translate(glm::vec3 translation) {
    this->_position += translation;
}

void Transform::scale(float t) {
    this->_scale *= t;
}

} // namespace engine::component