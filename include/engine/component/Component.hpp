#pragma once

#include "engine/component/Transform.hpp"

namespace engine::component {

class Component {
  public:
    Component();

    Component(Transform transform);

    Component(glm::vec3 position);

    Component(glm::vec3 position, Quaternion rotation);

    Component(glm::vec3 position, Quaternion rotation, glm::vec3 scale);

    // Can write to transform as well
    Transform &getTransform();

    void setTransform(Transform transform);

  private:
    Transform _transform;
};

} // namespace engine::component