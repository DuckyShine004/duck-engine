#pragma once

#include "engine/shader/Shader.hpp"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

using namespace engine::shader;

namespace engine::camera {

enum Direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

struct Rotation {
    float yaw;
    float pitch;

    glm::vec3 direction;

    Rotation() : yaw(0.0f), pitch(0.0f), direction(glm::vec3(0.0f)) {
    }
};

struct ViewComponents {
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 front;

    ViewComponents() : right(glm::vec3(0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)), front(glm::vec3(0.0f, 0.0f, -1.0f)) {
    }
};

struct ModelViewProjection {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    ModelViewProjection() : model(glm::mat4(1.0f)), view(glm::mat4(1.0f)), projection(glm::mat4(1.0f)) {
    }
};

class Camera {
  public:
    Camera();

    Camera(glm::vec3 position);

    Camera(float x, float y, float z);

    void update(GLFWwindow *window, float deltaTime);

    void updateView();

    void updateProjection();

    void uploadViewProjection(Shader &shader);

    void uploadModelViewProjection(Shader &shader);

    void move(Direction direction, float deltaTime);

    void rotate(glm::vec2 cursorPosition);

    glm::vec3 getFront();

    glm::vec3 getPosition();

  private:
    const float _FIELD_OF_VIEW = 45.0f;

    const float _NEAR = 0.1f;
    const float _FAR = 100.0f;

    const float _YAW = 90.0f;
    const float _PITCH = 0.0f;
    const float _PITCH_LIMIT = 89.0f;
    const float _SENSITIVITY = 0.025f;

    const float _SPEED = 10.0f;

    ModelViewProjection _mvp;

    ViewComponents _viewComponents;

    Rotation _rotation;

    glm::vec3 _position;

    glm::vec2 _lastCursorPosition;

    glm::vec2 getCursorOffset(glm::vec2 cursorPosition);
};

} // namespace engine::camera