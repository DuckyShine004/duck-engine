#pragma once

#include <glm/glm.hpp>

namespace engine::light {

class Light {
  public:
    Light();

    Light(glm::vec3 position);

    ~Light();

    glm::vec3 getPosition();

    void setAmbient(glm::vec3 ambient);
    void setAmbient(float r, float g, float b);

    glm::vec3 getAmbient();

    void setDiffuse(glm::vec3 diffuse);
    void setDiffuse(float r, float g, float b);

    glm::vec3 getDiffuse();

    void setSpecular(glm::vec3 specular);
    void setSpecular(float r, float g, float b);

    glm::vec3 getSpecular();

  private:
    glm::vec3 _position;

    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;
};

} // namespace engine::light
