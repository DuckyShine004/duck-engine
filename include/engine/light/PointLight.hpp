#pragma once

#include "engine/light/Light.hpp"

namespace engine::light {

class PointLight final : public Light {
  public:
    PointLight(int id, glm::vec3 position);

    ~PointLight();

    void setPosition(glm::vec3 position);
    void setPosition(float x, float y, float z);

    glm::vec3 getPosition();

    void upload(Shader &shader) override;

  private:
    const char *_NAME = "pointLight";

    glm::vec3 _position;
};

}; // namespace engine::light