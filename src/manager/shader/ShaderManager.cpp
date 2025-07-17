#include "manager/shader/ShaderManager.hpp"

#include "utility/file/FileUtility.hpp"

#include "logger/LoggerMacros.hpp"

using namespace utility::file;

namespace manager::shader {

ShaderManager::ShaderManager() = default;

ShaderManager::~ShaderManager() = default;

ShaderManager &ShaderManager::getInstance() {
    static ShaderManager instance;

    return instance;
}

void ShaderManager::initialise() {
    std::vector<std::string> paths = FileUtility::getFilesInDirectory(this->_DIRECTORY);

    for (const std::string &path : paths) {
        this->addShader(path);
    }
}

Shader &ShaderManager::getShader(const std::string &name) {
    if (this->_shaders.find(name) == this->_shaders.end()) {
        std::terminate();
    }

    return *(this->_shaders.at(name));
}

void ShaderManager::addShader(const std::string &path) {
    std::string basename = FileUtility::getBasenameFromPath(path);

    std::string parentDirectory = FileUtility::getParentDirectory(path);

    std::string shaderPath = parentDirectory + '/' + basename;

    if (this->_shaders.find(basename) != this->_shaders.end()) {
        LOG_WARN("{} is already loaded, skipping...", path);
        return;
    }

    std::string vertexShaderPath = shaderPath + this->_VERTEX_SHADER_EXTENSION;
    std::string fragmentShaderPath = shaderPath + this->_FRAGMENT_SHADER_EXTENSION;

    std::unique_ptr<Shader> shader = std::make_unique<Shader>(vertexShaderPath, fragmentShaderPath);

    this->_shaders.emplace(basename, std::move(shader));
}

}; // namespace manager::shader