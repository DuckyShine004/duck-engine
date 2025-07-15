#pragma once

#include <glm/glm.hpp>

namespace engine::camera {

class Camera {
  public:
    Camera();

    void updateAspectRatio(int width, int height);

    glm::mat4 getProjectionMatrix();

  private:
    glm::mat4 _projectionMatrix;
};

} // namespace engine::camera