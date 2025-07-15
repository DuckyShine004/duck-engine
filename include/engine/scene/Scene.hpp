#pragma once

#include "engine/shader/Shader.hpp"

#include "engine/model/Model.hpp"

using namespace engine::shader;

using namespace engine::model;

namespace engine::scene {

class Scene {
  public:
    Scene();

    void render();

  private:
    Shader _shader;

    std::vector<Model> _models;

    void initialise();
};

} // namespace engine::scene