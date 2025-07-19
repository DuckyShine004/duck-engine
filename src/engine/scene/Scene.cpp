#include "engine/scene/Scene.hpp"

#include "engine/light/PointLight.hpp"

#include "manager/shader/ShaderManager.hpp"

#include "manager/display/DisplayManager.hpp"

#include "logger/LoggerMacros.hpp"

using namespace engine::light;

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

void Scene::renderGrid() {
    Shader &shader = ShaderManager::getInstance().getShader("grid");

    shader.use();

    this->_camera.uploadViewProjection(shader);

    GLuint gridVAO;

    glGenVertexArrays(1, &gridVAO);
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(gridVAO);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glBindVertexArray(0);
}

void Scene::render() {
    this->renderGrid();
    Shader &shader = ShaderManager::getInstance().getShader("scene");

    shader.use();

    // Set uniforms or what not before drawing
    this->_camera.uploadModelViewProjection(shader);
    shader.setVector3f("uViewPosition", this->_camera.getPosition());

    PointLight light(0, glm::vec3(5.0f));

    light.setAmbient(glm::vec3(0.2f));
    light.setDiffuse(glm::vec3(0.5f));
    light.setSpecular(glm::vec3(1.0f));

    shader.setVector3f("light.position", light.getPosition());
    shader.setVector3f("light.ambient", light.getAmbient());
    shader.setVector3f("light.diffuse", light.getDiffuse());
    shader.setVector3f("light.specular", light.getSpecular());

    for (Model &model : this->_models) {
        model.draw(shader);
    }
}

Camera &Scene::getCamera() {
    return this->_camera;
}

} // namespace engine::scene