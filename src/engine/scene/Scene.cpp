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
    Shader &tempshader = ShaderManager::getInstance().getShader("grid");

    tempshader.use();

    this->_camera.uploadViewProjection(tempshader);

    GLuint gridVAO;

    glGenVertexArrays(1, &gridVAO);
    // No VBO needed: we'll generate positions in the vertex shader via gl_VertexID
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindVertexArray(gridVAO);

    // draw two triangles (6 vertices) using gl_VertexID to pull from your
    // `const vec3 gridPlane[6]` array
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    // (Optional) unbind
    glBindVertexArray(0);

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