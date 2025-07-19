#pragma once

#include "engine/light/Light.hpp"
#include "engine/light/Attenuation.hpp"

namespace engine::light {

class SpotLight final : public Light {
  public:
    SpotLight(int id, glm::vec3 position, glm::vec3 direction);

    ~SpotLight();

    void setPosition(glm::vec3 position);
    void setPosition(float x, float y, float z);

    glm::vec3 getPosition();

    void setDirection(glm::vec3 direction);
    void setDirection(float x, float y, float z);

    glm::vec3 getDirection();

    void setInnerCutoff(float innerCutoff);

    float getInnerCutoff();

    void setOuterCutoff(float outerCutoff);

    float getOuterCutoff();

    void setAttenuation(Attenuation attenuation);
    void setAttenuation(float constant, float linear, float quadratic);

    Attenuation getAttenuation();

    void upload(Shader &shader) override;

  private:
    static constexpr const char *_NAME = "flashLight";

    glm::vec3 _position;
    glm::vec3 _direction;

    Attenuation _attenuation;

    float _innerCutoff;
    float _outerCutoff;
};

}; // namespace engine::light