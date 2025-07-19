#include "engine/light/PointLight.hpp"

namespace engine::light {

PointLight::PointLight(int id, glm::vec3 position) : Light(id, this->_NAME), _position(position) {
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

void PointLight::setAttenuation(Attenuation attenuation) {
    this->_attenuation = attenuation;
}

void PointLight::setAttenuation(float constant, float linear, float quadratic) {
    this->setAttenuation(Attenuation{constant, linear, quadratic});
}

Attenuation PointLight::getAttenutation() {
    return this->_attenuation;
}

void PointLight::upload(Shader &shader) {
    Light::upload(shader);

    std::string name = this->getUniformName();

    shader.setVector3f(name.c_str(), this->_position);
}

}; // namespace engine::light