#include "engine/scene/Scene.hpp"

#include "engine/light/SpotLight.hpp"
#include "engine/light/PointLight.hpp"

#include "engine/sound/SoundPlayer.hpp"
#include "engine/sound/SoundBuffer.hpp"
#include "engine/sound/SoundSource.hpp"

#include "manager/shader/ShaderManager.hpp"

#include "manager/display/DisplayManager.hpp"

#include "logger/LoggerMacros.hpp"

using namespace engine::light;

using namespace engine::sound;

using namespace manager::shader;

using namespace manager::display;

namespace engine::scene {

Scene::Scene() = default;

void Scene::load() {
    // Model cat("resources/models/cat/12222_Cat_v1_l3.obj");
    Model duck("resources/models/duck/Duck.obj");

    this->_models.push_back(duck);
    // this->_models.push_back(cat);

    ALuint soundId = SoundBuffer::getInstance().addSound("resources/sounds/cat.mp3");

    this->_source.play(soundId);
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

    SpotLight light(0, this->_camera.getPosition(), this->_camera.getFront());
    // PointLight light(0, glm::vec3(5.0f));

    light.setAmbient(glm::vec3(0.2f));
    light.setDiffuse(glm::vec3(0.8f));
    light.setSpecular(glm::vec3(1.0f));
    light.setAttenuation(1.0f, 0.09f, 0.032f);
    light.setInnerCutoff(glm::cos(glm::radians(12.5f)));
    light.setOuterCutoff(glm::cos(glm::radians(17.5f)));

    shader.setVector3f("light.position", light.getPosition());
    shader.setVector3f("light.direction", light.getDirection());
    shader.setVector3f("light.ambient", light.getAmbient());
    shader.setVector3f("light.diffuse", light.getDiffuse());
    shader.setVector3f("light.specular", light.getSpecular());
    shader.setFloat("light.constant", light.getAttenuation().constant);
    shader.setFloat("light.linear", light.getAttenuation().linear);
    shader.setFloat("light.quadratic", light.getAttenuation().quadratic);
    shader.setFloat("light.innerCutoff", light.getInnerCutoff());
    shader.setFloat("light.outerCutoff", light.getOuterCutoff());

    for (Model &model : this->_models) {
        model.draw(shader);
    }
}

Camera &Scene::getCamera() {
    return this->_camera;
}

} // namespace engine::scene