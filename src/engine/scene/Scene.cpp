#include "engine/scene/Scene.hpp"

#include "logger/LoggerMacros.hpp"

namespace engine::scene {

Scene::Scene() = default;

void Scene::load() {
    this->_shader = Shader("shaders/scene/scene");

    Model model("resources/models/duck.obj");

    this->_models.push_back(model);
}

void Scene::render() {
    this->_shader.use();

    for (Model &model : this->_models) {
        model.draw(this->_shader);
    }
}

} // namespace engine::scene