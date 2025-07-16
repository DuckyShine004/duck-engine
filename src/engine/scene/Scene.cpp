#include "engine/scene/Scene.hpp"

#include "manager/display/DisplayManager.hpp"

#include "logger/LoggerMacros.hpp"

using namespace manager::display;

namespace engine::scene {

Scene::Scene() = default;

void Scene::load() {
    this->_shader = Shader("shaders/scene/scene");

    Model model("resources/models/duck.obj");

    this->_models.push_back(model);
}

void Scene::update() {
    this->_camera.updateModelViewProjection();
}

void Scene::updateResolution(int width, int height) {
    DisplayManager::getInstance().updateResolution(width, height);

    this->_camera.updateProjection();
}

void Scene::render() {
    this->_shader.use();

    // Set uniforms or what not before drawing
    this->_camera.uploadModelViewProjection(this->_shader);

    for (Model &model : this->_models) {
        model.draw(this->_shader);
    }
}

Camera &Scene::getCamera() {
    return this->_camera;
}

} // namespace engine::scene