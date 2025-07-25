#include "engine/model/Mesh.hpp"

#include "logger/LoggerMacros.hpp"

namespace engine::model {

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, Material material)
    : _vertices(vertices), _indices(indices), _textures(textures), _material(material) {
    this->initialise();
}

void Mesh::draw(Shader &shader) {
    unsigned int diffuseNumber = 1;
    unsigned int specularNumber = 1;

    // Upload the materials
    // LOG_DEBUG("Ambient: {}, {}, {}", this->_material.ambient.x, this->_material.ambient.y, this->_material.ambient.z);
    // LOG_DEBUG("Diffuse: {}, {}, {}", this->_material.diffuse.x, this->_material.diffuse.y, this->_material.diffuse.z);
    // LOG_DEBUG("Specular: {}, {}, {}", this->_material.specular.x, this->_material.specular.y, this->_material.specular.z);
    // LOG_DEBUG("Shininess: {}", this->_material.shininess);

    shader.setVector3f("material.ambient", this->_material.ambient);
    shader.setVector3f("material.diffuse", this->_material.diffuse);
    shader.setVector3f("material.specular", this->_material.specular);

    shader.setFloat("material.shininess", this->_material.shininess);

    for (unsigned int unit = 0; unit < this->_textures.size(); unit++) {
        glActiveTexture(GL_TEXTURE0 + unit);

        std::string number;
        std::string name = this->_textures[unit].type;

        if (name == "texture_diffuse") {
            number = std::to_string(diffuseNumber++);
        } else if (name == "texture_specular") {
            number = std::to_string(specularNumber++);
        }

        std::string materialName = name + number;

        shader.setInteger(materialName.c_str(), unit);

        glBindTexture(GL_TEXTURE_2D, this->_textures[unit].id);
    }

    glBindVertexArray(this->_vao);
    glDrawElements(GL_TRIANGLES, this->_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}

void Mesh::initialise() {
    glGenVertexArrays(1, &this->_vao);

    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);

    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, this->_vertices.size() * sizeof(Vertex), &this->_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_indices.size() * sizeof(unsigned int), &this->_indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, textureCoordinates));

    glBindVertexArray(0);
}

} // namespace engine::model