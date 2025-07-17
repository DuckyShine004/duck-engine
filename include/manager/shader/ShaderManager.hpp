#pragma once

#include "manager/Manager.hpp"

#include "engine/shader/Shader.hpp"

#include <map>
#include <memory>

using namespace engine::shader;

namespace manager::shader {

class ShaderManager final : public Manager {
  public:
    static ShaderManager &getInstance();

    Shader *getShader(const std::string &name);

    void initialise();

  private:
    const char *_DIRECTORY = "shaders/";

    const char *_VERTEX_FILE_FORMAT = ".vert";
    const char *_FRAGMENT_FILE_FORMAT = ".frag";

    ShaderManager();

    ~ShaderManager();

    void addShader(const std::string &path);

    std::map<std::string, std::unique_ptr<Shader>> _shaders;
};

}; // namespace manager::shader