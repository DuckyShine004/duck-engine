#pragma once

#include "engine/shader/Shader.hpp"

#include "engine/model/Model.hpp"

#include "engine/camera/Camera.hpp"

using namespace engine::shader;

using namespace engine::model;

using namespace engine::camera;

namespace engine::scene {

class Scene {
  public:
    Scene();

    void load();

    void render();

    void updateResolution(int width, int height);

  private:
    Shader _shader;

    Camera _camera;

    std::vector<Model> _models;
};

} // namespace engine::scene