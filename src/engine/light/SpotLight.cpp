#include "engine/light/SpotLight.hpp"

namespace engine::light {

SpotLight::SpotLight(int id, glm::vec3 position, glm::vec3 direction) : Light(id, this->_NAME), _position(position), _direction(direction) {
}

SpotLight::~SpotLight() = default;

void SpotLight::setPosition(glm::vec3 position) {
    this->_position = position;
}

void SpotLight::setPosition(float x, float y, float z) {
    this->setPosition(glm::vec3(x, y, z));
}

glm::vec3 SpotLight::getPosition() {
    return this->_position;
}

void SpotLight::setDirection(glm::vec3 direction) {
    this->_direction = direction;
}

void SpotLight::setDirection(float x, float y, float z) {
    this->setDirection(glm::vec3(x, y, z));
}

glm::vec3 SpotLight::getDirection() {
    return this->_direction;
}

void SpotLight::setInnerCutoff(float innerCutoff) {
    this->_innerCutoff = innerCutoff;
}

float SpotLight::getInnerCutoff() {
    return this->_innerCutoff;
}

void SpotLight::setOuterCutoff(float outerCutoff) {
    this->_outerCutoff = outerCutoff;
}

float SpotLight::getOuterCutoff() {
    return this->_outerCutoff;
}

void SpotLight::upload(Shader &shader) {
    Light::upload(shader);

    std::string name = this->getUniformName();

    shader.setVector3f(name.c_str(), this->_position);
    shader.setVector3f(name.c_str(), this->_direction);

    shader.setFloat(name.c_str(), this->_innerCutoff);
    shader.setFloat(name.c_str(), this->_outerCutoff);
}

}; // namespace engine::light