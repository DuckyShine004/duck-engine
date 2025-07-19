#pragma once

#include "engine/shader/Shader.hpp"

#include <glm/glm.hpp>

#include <string>

using namespace engine::shader;

namespace engine::light {

class Light {
  public:
    Light(int id, std::string name);

    ~Light();

    void setAmbient(glm::vec3 ambient);
    void setAmbient(float r, float g, float b);

    glm::vec3 getAmbient();

    void setDiffuse(glm::vec3 diffuse);
    void setDiffuse(float r, float g, float b);

    glm::vec3 getDiffuse();

    void setSpecular(glm::vec3 specular);
    void setSpecular(float r, float g, float b);

    glm::vec3 getSpecular();

    std::string getUniformName();

    virtual void upload(Shader &shader);

  protected:
    int _id;

    std::string _name;

  private:
    glm::vec3 _ambient;
    glm::vec3 _diffuse;
    glm::vec3 _specular;
};

} // namespace engine::light
