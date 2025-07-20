#include "engine/component/Component.hpp"

namespace engine::component {

Component::Component() = default;

Component::Component(Transform transform) : _transform(transform) {
}

Component::Component(glm::vec3 position) : _transform(position) {
}

Component::Component(glm::vec3 position, Quaternion rotation) : _transform(position, rotation) {
}

Component::Component(glm::vec3 position, Quaternion rotation, glm::vec3 scale) : _transform(position, rotation, scale) {
}

Transform &Component::getTransform() {
    return this->_transform;
}

void Component::setTransform(Transform transform) {
    this->_transform = transform;
}

} // namespace engine::component