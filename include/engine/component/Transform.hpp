#pragma once

#include "engine/math/Quaternion.hpp"

using namespace engine::math;

namespace engine::component {
class Transform {
  public:
    Transform();

    Transform(glm::vec3 position);

    Transform(glm::vec3 position, Quaternion rotation);

    Transform(glm::vec3 position, Quaternion rotation, glm::vec3 scale);

    glm::vec3 getPosition();

    void setPosition(glm::vec3 position);

    Quaternion getRotation();

    void setRotation(Quaternion rotation);

    glm::vec3 getScale();

    void setScale(glm::vec3 scale);

    // Translate from old x to new x, addition of vectors
    void translate(glm::vec3 translation);

    void rotate();

    void scale(float t);

  private:
    glm::vec3 _position;

    Quaternion _rotation;

    glm::vec3 _scale;
};

} // namespace engine::component