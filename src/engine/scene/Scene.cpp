#include "engine/scene/Scene.hpp"

#include "logger/LoggerMacros.hpp"

namespace engine::scene {

Scene::Scene() = default;

void Scene::load() {
    this->_shader = Shader("shaders/scene/scene");

    Model model("resources/models/duck.obj");

    this->_models.push_back(model);
}

void Scene::updateResolution(int width, int height) {
    this->_camera.updateAspectRatio(width, height);
}

void Scene::render() {
    this->_shader.use();

    // Set uniforms or what not before drawing
    this->_shader.setMatrix4fv("uProjection", this->_camera.getProjectionMatrix());

    for (Model &model : this->_models) {
        model.draw(this->_shader);
    }
}

} // namespace engine::scene