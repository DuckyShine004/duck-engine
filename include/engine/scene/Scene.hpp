#pragma once

#include "engine/shader/Shader.hpp"

#include "engine/model/Model.hpp"

#include "engine/camera/Camera.hpp"

#include <GLFW/glfw3.h>

using namespace engine::shader;

using namespace engine::model;

using namespace engine::camera;

namespace engine::scene {

class Scene {
  public:
    Scene();

    void load();

    void update(GLFWwindow *window, float deltaTime);

    void updateResolution(int width, int height);

    void render();

    Camera &getCamera();

  private:
    Shader _shader;

    Camera _camera;

    std::vector<Model> _models;

    float _aspectRatio;
};

} // namespace engine::scene