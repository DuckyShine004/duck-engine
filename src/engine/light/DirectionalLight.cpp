#include "engine/light/DirectionalLight.hpp"

namespace engine::light {

DirectionalLight::DirectionalLight(int id, glm::vec3 direction) : Light(id, this->_NAME), _direction(direction) {
}

DirectionalLight::~DirectionalLight() = default;

void DirectionalLight::setDirection(glm::vec3 direction) {
    this->_direction = direction;
}

void DirectionalLight::setDirection(float x, float y, float z) {
    this->setDirection(glm::vec3(x, y, z));
}

void DirectionalLight::setSphericalDirection(glm::vec3 sphericalDirection) {
    glm::vec3 direction;

    direction.x = sphericalDirection.x * glm::sin(sphericalDirection.z) * glm::cos(sphericalDirection.y);
    direction.y = sphericalDirection.x * glm::sin(sphericalDirection.z) * glm::sin(sphericalDirection.y);
    direction.z = sphericalDirection.x * glm::cos(sphericalDirection.z);

    this->setDirection(direction);
}

void DirectionalLight::setSphericalDirection(float rho, float theta, float phi) {
    this->setSphericalDirection(glm::vec3(rho, theta, phi));
}

void DirectionalLight::upload(Shader &shader) {
    Light::upload(shader);

    std::string name = this->getUniformName();

    shader.setVector3f(name.c_str(), this->_direction);
}

}; // namespace engine::light