#pragma once

#include "engine/shader/Shader.hpp"

#include "engine/model/Model.hpp"

using namespace engine::shader;

using namespace engine::model;

namespace engine::scene {

class Scene {
  public:
    Scene();

    void load();

    void render();

  private:
    Shader _shader;

    std::vector<Model> _models;
};

} // namespace engine::scene