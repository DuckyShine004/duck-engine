#pragma once

#include "engine/shader/Shader.hpp"

#include "engine/model/Mesh.hpp"

#include <assimp/scene.h>

#include <stb/stb_image.h>

#include <string>
#include <vector>

using namespace engine::shader;

namespace engine::model {

class Model {
  public:
    Model(char *path);

    void draw(Shader &shader);

  private:
    std::vector<Mesh> _meshes;

    std::vector<Texture> _loadedTextures;

    std::string _directory;

    void loadModel(std::string path);

    void processNode(aiNode *node, const aiScene *scene);

    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture> loadTexturesFromMaterial(aiMaterial *material, aiTextureType type, std::string name);

    unsigned int getTextureIdFromFile(const char *path, const std::string &directory);
};

} // namespace engine::model