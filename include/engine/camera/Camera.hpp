#pragma once

#include "engine/shader/Shader.hpp"

#include <glm/glm.hpp>

using namespace engine::shader;

namespace engine::camera {

struct ModelViewProjection {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    ModelViewProjection() : model(glm::mat4(1.0f)), view(glm::mat4(1.0f)), projection(glm::mat4(1.0f)) {
    }
};

class Camera {
  public:
    Camera();

    Camera(glm::vec3 position);

    Camera(float x, float y, float z);

    void updateAspectRatio();

    void update();

    void updateModelViewProjectionMatrices();
    void uploadModelViewProjectionMatrices(Shader &shader);

    glm::mat4 getProjectionMatrix();

  private:
    const float _FIELD_OF_VIEW = 45.0f;

    const float _NEAR = 0.1f;
    const float _FAR = 100.0f;

    ModelViewProjection _mvp;

    glm::vec3 _position;
};

} // namespace engine::camera