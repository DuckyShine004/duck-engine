#pragma once

namespace engine::light {

struct Attenuation {
    float constant;
    float linear;
    float quadratic;
};

}; // namespace engine::light