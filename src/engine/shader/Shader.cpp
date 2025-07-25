#include "external/glad/glad.h"

#include "engine/shader/Shader.hpp"

#include "utility/file/FileUtility.hpp"

#include "logger/LoggerMacros.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace utility::file;

namespace engine::shader {

Shader::Shader() = default;

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) : _vertexShaderPath(vertexShaderPath), _fragmentShaderPath(fragmentShaderPath) {
    this->initialise();
}

void Shader::initialise() {
    this->createShaders();

    this->compileShaders();

    this->attachShaders();

    this->linkProgram();

    this->deleteShaders();
}

void Shader::use() {
    glUseProgram(this->_program);
}

void Shader::detach() {
    glUseProgram(0);
}

void Shader::createShaders() {
    std::string vertexShaderSource = FileUtility::getFileToString(this->_vertexShaderPath);
    std::string fragmentShaderSource = FileUtility::getFileToString(this->_fragmentShaderPath);

    const char *vertexShaderCode = vertexShaderSource.c_str();
    const char *fragmentShaderCode = fragmentShaderSource.c_str();

    this->_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    this->_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(this->_vertexShader, 1, &vertexShaderCode, nullptr);
    glShaderSource(this->_fragmentShader, 1, &fragmentShaderCode, nullptr);
}

void Shader::compileShaders() {
    glCompileShader(this->_vertexShader);

    this->checkCompilationStatus(this->_vertexShader);

    glCompileShader(this->_fragmentShader);

    this->checkCompilationStatus(this->_fragmentShader);
}

void Shader::attachShaders() {
    this->_program = glCreateProgram();

    glAttachShader(this->_program, this->_vertexShader);
    glAttachShader(this->_program, this->_fragmentShader);
}

void Shader::linkProgram() {
    glLinkProgram(this->_program);

    this->checkProgramLinkStatus();
}

void Shader::deleteShaders() {
    glDeleteShader(this->_vertexShader);
    glDeleteShader(this->_fragmentShader);
}

void Shader::checkCompilationStatus(GLuint shader) {
    GLint status;

    GLchar infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);

        LOG_ERROR("Compile Error: \n {}", infoLog);
    }
}

void Shader::checkProgramLinkStatus() {
    GLint status;

    GLchar infoLog[512];

    glGetProgramiv(this->_program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        glGetProgramInfoLog(this->_program, 512, nullptr, infoLog);

        LOG_ERROR("Link Error: \n {}", infoLog);
    }
}

void Shader::setFloat(const GLchar *name, float value) {
    GLint location = glGetUniformLocation(this->_program, name);

    glUniform1f(location, value);
}

void Shader::setInteger(const GLchar *name, int value) {
    GLint location = glGetUniformLocation(this->_program, name);

    glUniform1i(location, value);
}

void Shader::setVector3f(const GLchar *name, glm::vec3 vector) {
    GLint location = glGetUniformLocation(this->_program, name);

    glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::setMatrix4fv(const GLchar *name, glm::mat4 matrix) {
    GLint location = glGetUniformLocation(this->_program, name);

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace engine::shader