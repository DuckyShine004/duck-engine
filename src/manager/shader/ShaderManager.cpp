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
        LOG_DEBUG("Shader path: {}", path);
        this->addShader(path);
    }
}

Shader *ShaderManager::getShader(const std::string &name) {
    if (this->_shaders.find(name) == this->_shaders.end()) {
        return nullptr;
    }

    return this->_shaders[name].get();
}

void ShaderManager::addShader(const std::string &path) {
    std::string filename = FileUtility::getFilenameFromPath(path);

    if (this->_shaders.find(filename) != this->_shaders.end()) {
        LOG_WARN("Skipping shader: {}", path);
        return;
    }

    std::string vertexShaderPath = filename + ".vert";
    std::string fragmentShaderPath = filename + ".frag";

    std::unique_ptr<Shader> shader = std::make_unique<Shader>(vertexShaderPath, fragmentShaderPath);

    this->_shaders.emplace(filename, std::move(shader));
}

}; // namespace manager::shader