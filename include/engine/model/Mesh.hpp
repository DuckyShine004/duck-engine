#pragma once

#include "external/glad/glad.h"

#include "engine/shader/Shader.hpp"

#include "engine/model/Vertex.hpp"
#include "engine/model/Texture.hpp"
#include "engine/model/Material.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>

using namespace engine::shader;

namespace engine::model {

class Mesh {
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material material);

    void draw(Shader &shader);

  private:
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;

    std::vector<Vertex> _vertices;

    std::vector<unsigned int> _indices;

    std::vector<Texture> _textures;

    Material _material;

    void initialise();
};

} // namespace engine::model