#pragma once

#include "external/glad/glad.h"

#include "engine/shader/Shader.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>

using namespace engine::shader;

namespace engine::model {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;

    glm::vec2 textureCoordinates;
};

struct Texture {
    unsigned int id;

    std::string type;
};

class Mesh {
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    void draw(Shader &shader);

  private:
    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;

    std::vector<Vertex> _vertices;

    std::vector<unsigned int> _indices;

    std::vector<Texture> _textures;

    void initialise();
};

} // namespace engine::model