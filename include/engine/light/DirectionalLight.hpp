#pragma once

#include "engine/light/Light.hpp"

namespace engine::light {

// Expect cartesian coordinates
class DirectionalLight final : public Light {
  public:
    DirectionalLight(int id, glm::vec3 direction);

    ~DirectionalLight();

    void setDirection(glm::vec3 direction);
    void setDirection(float x, float y, float z);

    void setSphericalDirection(glm::vec3 sphericalDirection);
    void setSphericalDirection(float rho, float theta, float phi);

    void upload(Shader &shader) override;

  private:
    static constexpr const char *_NAME = "directionalLight";

    glm::vec3 _direction;
};

}; // namespace engine::light