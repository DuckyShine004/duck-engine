#pragma once

#include <string>

namespace engine::model {

struct Texture {
    unsigned int id;

    std::string type;
    std::string path;
};

} // namespace engine::model