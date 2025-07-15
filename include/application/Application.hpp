#pragma once

#include "engine/scene/Scene.hpp"

#include <GLFW/glfw3.h>

using namespace engine::scene;

namespace application {

class Application {
  public:
    Application();

    void initialise();

    void load();

    void run();

  private:
    GLFWwindow *_window;

    Scene _scene;

    float _lastTime;

    float _framesPerSecond;

    void update();

    void render();

    void setWindowSize(int width, int height);

    void onResize(GLFWwindow *window, int width, int height);
};

} // namespace application
