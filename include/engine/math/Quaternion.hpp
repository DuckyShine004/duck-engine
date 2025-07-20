#pragma once

#include <glm/glm.hpp>

#include <string>

namespace engine::math {

// Using euler then transforming into quats
class Quaternion {
  public:
    Quaternion(float x, float y, float z);

    Quaternion(float w, float x, float y, float z);

    Quaternion(float s, glm::vec3 v);

    float getW();
    float getX();
    float getY();
    float getZ();

    Quaternion slerp(Quaternion quaternion, float t);

    glm::vec3 toEuler();

    float dot(Quaternion quaternion);

    Quaternion pow(float t);

    float length();
    float lengthSquared();

    Quaternion cross(Quaternion quaternion);

    Quaternion normalise();

    Quaternion inverse();

    std::string toString();

    Quaternion operator*(Quaternion quaternion);
    Quaternion operator/(float t);

    static Quaternion slerp(Quaternion q0, Quaternion q1, float t);

    static Quaternion toQuaternion(float x, float y, float z);
    static glm::vec3 toEuler(Quaternion quaternion);

    static float dot(Quaternion q0, Quaternion q1);

    static Quaternion pow(Quaternion quaternion, float t);

    static float length(Quaternion quaternion);
    static float lengthSquared(Quaternion quaternion);

    // More idiomatic representation of cross product
    static Quaternion cross(Quaternion q0, Quaternion q1);

    static Quaternion normalise(Quaternion quaternion);

    static Quaternion inverse(Quaternion quaternion);

    static std::string toString(Quaternion quaternion);

  private:
    static constexpr const float _EPSILON = 1e-6f;

    float _w;
    float _x;
    float _y;
    float _z;
};

}; // namespace engine::math