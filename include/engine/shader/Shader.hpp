#pragma once

#include "external/glad/glad.h"

#include <glm/glm.hpp>

#include <string>

namespace engine::shader {

class Shader {
  public:
    Shader();

    Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);

    void use();
    void detach();

    void setFloat(const GLchar *name, float value);

    void setInteger(const GLchar *name, int value);

    void setVector3f(const GLchar *name, glm::vec3 vector);

    void setMatrix4fv(const GLchar *name, glm::mat4 matrix);

  private:
    std::string _vertexShaderPath;
    std::string _fragmentShaderPath;

    GLuint _vertexShader;
    GLuint _fragmentShader;

    GLuint _program;

    void initialise();

    void createShaders();
    void compileShaders();
    void attachShaders();
    void linkProgram();
    void deleteShaders();

    void checkCompilationStatus(GLuint shader);
    void checkProgramLinkStatus();
};

} // namespace engine::shader