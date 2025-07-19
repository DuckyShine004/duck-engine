#include "engine/light/Light.hpp"

namespace engine::light {

Light::Light(int id, std::string name) : _id(id), _name(name) {
}

Light::~Light() = default;

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

std::string Light::getUniformName() {
    return this->_name + '[' + std::to_string(this->_id) + ']';
}

void Light::upload(Shader &shader) {
    std::string name = this->getUniformName();

    shader.setVector3f(name.c_str(), this->_ambient);
    shader.setVector3f(name.c_str(), this->_diffuse);
    shader.setVector3f(name.c_str(), this->_specular);
}

} // namespace engine::light