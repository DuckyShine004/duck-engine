#include "engine/scene/Scene.hpp"

namespace engine::scene {

Scene::Scene() {
    this->initialise();
}

void Scene::initialise() {
    this->_shader = Shader("shaders/scene/scene");

    this->_models.push_back(Model("resources/models/duck.obj"));
}

void Scene::render() {
    this->_shader.use();

    for (Model &model : this->_models) {
        model.draw(this->_shader);
    }
}

} // namespace engine::scene