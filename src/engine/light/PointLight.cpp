#include "engine/light/PointLight.hpp"

namespace engine::light {

PointLight::PointLight(glm::vec3 position) : _position(position) {
}

PointLight::~PointLight() = default;

void PointLight::setPosition(glm::vec3 position) {
    this->_position = position;
}

void PointLight::setPosition(float x, float y, float z) {
    this->setPosition(glm::vec3(x, y, z));
}

glm::vec3 PointLight::getPosition() {
    return this->_position;
}

}; // namespace engine::light