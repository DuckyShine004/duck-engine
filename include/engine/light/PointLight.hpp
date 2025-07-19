#pragma once

#include "engine/light/Light.hpp"
#include "engine/light/Attenuation.hpp"

namespace engine::light {

class PointLight final : public Light {
  public:
    PointLight(int id, glm::vec3 position);

    ~PointLight();

    void setPosition(glm::vec3 position);
    void setPosition(float x, float y, float z);

    glm::vec3 getPosition();

    void setAttenuation(Attenuation attenutation);
    void setAttenuation(float constant, float linear, float quadratic);

    Attenuation getAttenutation();

    void upload(Shader &shader) override;

  private:
    static constexpr const char *_NAME = "pointLight";

    glm::vec3 _position;

    Attenuation _attenuation;
};

}; // namespace engine::light