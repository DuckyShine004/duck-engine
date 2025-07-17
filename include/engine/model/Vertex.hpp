#pragma once

#include <glm/glm.hpp>

namespace engine::model {

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;

    glm::vec2 textureCoordinates;
};

} // namespace engine::model