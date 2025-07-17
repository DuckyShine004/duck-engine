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

    Shader &getShader(const std::string &name);

    void initialise();

  private:
    const char *_DIRECTORY = "shaders/";

    const char *_VERTEX_SHADER_EXTENSION = ".vert";
    const char *_FRAGMENT_SHADER_EXTENSION = ".frag";

    ShaderManager();

    ~ShaderManager();

    void addShader(const std::string &path);

    std::map<std::string, std::unique_ptr<Shader>> _shaders;
};

}; // namespace manager::shader