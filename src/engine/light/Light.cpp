#include "engine/light/Light.hpp"

namespace engine::light {

Light::Light() = default;

Light::Light(glm::vec3 position) {
    this->_position = position;
}

Light::~Light() = default;

glm::vec3 Light::getPosition() {
    return this->_position;
}

void Light::setAmbient(glm::vec3 ambient) {
    this->_ambient = ambient;
}

void Light::setAmbient(float r, float g, float b) {
    this->setAmbient(glm::vec3(r, g, b));
}

glm::vec3 Light::getAmbient() {
    return this->_ambient;
}

void Light::setDiffuse(glm::vec3 diffuse) {
    this->_diffuse = diffuse;
}

void Light::setDiffuse(float r, float g, float b) {
    this->setDiffuse(glm::vec3(r, g, b));
}

glm::vec3 Light::getDiffuse() {
    return this->_diffuse;
}

void Light::setSpecular(glm::vec3 specular) {
    this->_specular = specular;
}

void Light::setSpecular(float r, float g, float b) {
    this->setSpecular(glm::vec3(r, g, b));
}

glm::vec3 Light::getSpecular() {
    return this->_specular;
}

} // namespace engine::light