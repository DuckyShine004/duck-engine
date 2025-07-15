#define STB_IMAGE_IMPLEMENTATION

#include "external/glad/glad.h"

#include "application/Application.hpp"

#include "logger/LoggerMacros.hpp"

#include <stb/stb_image.h>

#include <iostream>

namespace application {

Application::Application() : _lastTime(0.0f), _framesPerSecond(0.0f) {
    stbi_set_flip_vertically_on_load(true);
}

void Application::initialise() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode *mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "Quaternion", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialise GLAD" << std::endl;

        return;
    }

    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        Application *application = static_cast<Application *>(glfwGetWindowUserPointer(window));

        application->onResize(window, width, height);
    });

    this->_window = window;
}

void Application::load() {
    int width;
    int height;

    glfwGetFramebufferSize(this->_window, &width, &height);

    this->setWindowSize(width, height);
}

void Application::run() {
    glfwSwapInterval(0);

    while (!glfwWindowShouldClose(this->_window)) {
        this->update();

        this->render();

        glfwSwapBuffers(this->_window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Application::update() {
    float time = glfwGetTime();

    float deltaTime = time - this->_lastTime;
}

void Application::render() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glClear(GL_COLOR_BUFFER_BIT);
}

void Application::onResize(GLFWwindow *window, int width, int height) {
    this->setWindowSize(width, height);
}

void Application::setWindowSize(int width, int height) {
    glViewport(0, 0, width, height);
}

} // namespace application
