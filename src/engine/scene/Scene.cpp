#include "engine/scene/Scene.hpp"

#include "manager/shader/ShaderManager.hpp"

#include "manager/display/DisplayManager.hpp"

#include "logger/LoggerMacros.hpp"

using namespace manager::shader;

using namespace manager::display;

namespace engine::scene {

Scene::Scene() = default;

void Scene::load() {
    Model model("resources/models/Duck.obj");

    this->_models.push_back(model);
}

void Scene::update(GLFWwindow *window, float deltaTime) {
    this->_camera.update(window, deltaTime);
}

void Scene::updateResolution(int width, int height) {
    DisplayManager::getInstance().updateResolution(width, height);

    this->_camera.updateProjection();
}

void Scene::render() {
    Shader &shader = ShaderManager::getInstance().getShader("scene");

    shader.use();

    // Set uniforms or what not before drawing
    this->_camera.uploadModelViewProjection(shader);

    for (Model &model : this->_models) {
        model.draw(shader);
    }
}

Camera &Scene::getCamera() {
    return this->_camera;
}

} // namespace engine::scene