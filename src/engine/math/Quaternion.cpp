#define GLM_ENABLE_EXPERIMENTAL

#include "engine/math/Quaternion.hpp"

#include <glm/gtx/quaternion.hpp>

#include <cmath>
#include <sstream>

#ifndef M_PI_2f
#define M_PI_2f (static_cast<float>(M_PI_2))
#endif

namespace engine::math {

Quaternion::Quaternion() : Quaternion(0.0f, 0.0f, 0.0f) {
}

// In the form of w + xi + yj + zk
Quaternion::Quaternion(float x, float y, float z) {
    float roll = glm::radians(x);
    float pitch = glm::radians(y);
    float yaw = glm::radians(z);

    float cr = glm::cos(roll * 0.5f);
    float sr = glm::sin(roll * 0.5f);

    float cp = glm::cos(pitch * 0.5f);
    float sp = glm::sin(pitch * 0.5f);

    float cy = glm::cos(yaw * 0.5f);
    float sy = glm::sin(yaw * 0.5f);

    this->_w = cr * cp * cy + sr * sp * sy;
    this->_x = sr * cp * cy - cr * sp * sy;
    this->_y = cr * sp * cy + sr * cp * sy;
    this->_z = cr * cp * sy - sr * sp * cy;
}

Quaternion::Quaternion(float w, float x, float y, float z) : _w(w), _x(x), _y(y), _z(z) {
}

Quaternion::Quaternion(float s, glm::vec3 v) : _w(s), _x(v.x), _y(v.y), _z(v.z) {
}

float Quaternion::getW() {
    return this->_w;
}

float Quaternion::getX() {
    return this->_x;
}

float Quaternion::getY() {
    return this->_y;
}

float Quaternion::getZ() {
    return this->_z;
}

Quaternion Quaternion::slerp(Quaternion quaternion, float t) {
    return Quaternion::slerp(*this, quaternion, t);
}

glm::vec3 Quaternion::toEuler() {
    return Quaternion::toEuler(*this);
}

float Quaternion::dot(Quaternion quaternion) {
    return Quaternion::dot(*this, quaternion);
}

Quaternion Quaternion::pow(float t) {
    return Quaternion::pow(*this, t);
}

float Quaternion::length() {
    return Quaternion::length(*this);
}

float Quaternion::lengthSquared() {
    return Quaternion::lengthSquared(*this);
}

Quaternion Quaternion::cross(Quaternion quaternion) {
    return Quaternion::cross(*this, quaternion);
}

Quaternion Quaternion::normalise() {
    return Quaternion::normalise(*this);
}

Quaternion Quaternion::inverse() {
    return Quaternion::inverse(*this);
}

std::string Quaternion::toString() {
    return Quaternion::toString(*this);
}

Quaternion Quaternion::operator*(Quaternion quaternion) {
    return Quaternion::cross(*this, quaternion);
}

Quaternion Quaternion::operator/(float t) {
    return Quaternion(this->_w / t, this->_x / t, this->_y / t, this->_z / t);
}

// Use * operand to understand equation better
Quaternion Quaternion::slerp(Quaternion q0, Quaternion q1, float t) {
    return (q1 * q0.inverse()).pow(t) * q0;
}

Quaternion Quaternion::toQuaternion(float x, float y, float z) {
    return Quaternion(x, y, z);
}

glm::vec3 Quaternion::toEuler(Quaternion quaternion) {
    glm::vec3 euler(0.0f);

    float rhoY = 2 * (quaternion._w * quaternion._x + quaternion._y * quaternion._z);
    float rhoX = 1 - 2 * (quaternion._x * quaternion._x + quaternion._y * quaternion._y);

    euler.x = std::atan2f(rhoY, rhoX);

    float thetaX = glm::sqrt(1 + 2 * (quaternion._w * quaternion._y - quaternion._x * quaternion._z));
    float thetaY = glm::sqrt(1 - 2 * (quaternion._w * quaternion._y - quaternion._x * quaternion._z));

    euler.y = 2 * std::atan2f(thetaY, thetaX) - M_PI_2f;

    float phiY = 2 * (quaternion._w * quaternion._z + quaternion._x * quaternion._y);
    float phiX = 1 - 2 * (quaternion._y * quaternion._y + quaternion._z * quaternion._z);

    euler.z = std::atan2f(phiY, phiX);

    return euler;
}

float Quaternion::dot(Quaternion q0, Quaternion q1) {
    float dw = q0._w * q1._w;
    float dx = q0._x * q1._x;
    float dy = q0._y * q1._y;
    float dz = q0._z * q1._z;

    return dw + dx + dy + dz;
}

Quaternion Quaternion::pow(Quaternion quaternion, float t) {
    Quaternion q = quaternion.normalise();

    float theta = glm::acos(q._w);

    glm::vec3 u = glm::normalize(glm::vec3(q._x, q._y, q._z));

    float cosTheta = glm::cos(t * theta);
    float sinTheta = glm::sin(t * theta);

    return Quaternion(cosTheta, u * sinTheta);
}

float Quaternion::length(Quaternion quaternion) {
    return glm::sqrt(Quaternion::lengthSquared(quaternion));
}

float Quaternion::lengthSquared(Quaternion quaternion) {
    return quaternion._w * quaternion._w + quaternion._x * quaternion._x + quaternion._y * quaternion._y + quaternion._z * quaternion._z;
}

Quaternion Quaternion::cross(Quaternion q0, Quaternion q1) {
    float w = q0._w * q1._w - q0._x * q1._x - q0._y * q1._y - q0._z * q1._z;
    float x = q0._w * q1._x + q0._x * q1._w + q0._y * q1._z - q0._z * q1._y;
    float y = q0._w * q1._y - q0._x * q1._z + q0._y * q1._w + q0._z * q1._x;
    float z = q0._w * q1._z + q0._x * q1._y - q0._y * q1._x + q0._z * q1._w;

    return Quaternion(w, x, y, z);
}

Quaternion Quaternion::normalise(Quaternion quaternion) {
    float length = quaternion.length();

    return (length <= _EPSILON) ? quaternion : quaternion / length;
}

Quaternion Quaternion::inverse(Quaternion quaternion) {
    Quaternion conjugate(quaternion._w, -quaternion._x, -quaternion._y, -quaternion._z);

    float lengthSquared = quaternion.lengthSquared();

    return (lengthSquared <= _EPSILON) ? conjugate : conjugate / lengthSquared;
}

Quaternion Quaternion::angleAxis(float angle, glm::vec3 axis) {
    float theta = glm::radians(angle);

    float cosTheta = glm::cos(theta / 2);
    float sinTheta = glm::sin(theta / 2);

    axis = glm::normalize(axis);

    return Quaternion(cosTheta, axis * sinTheta);
}

// Perhaps skip conversion to glm quat and manually convert if performance is an issue
glm::mat4 Quaternion::toMatrix(Quaternion quaternion) {
    glm::quat q(quaternion._w, quaternion._x, quaternion._y, quaternion._z);

    return glm::toMat4(q);
}

std::string Quaternion::toString(Quaternion quaternion) {
    std::ostringstream oss;

    oss << "Quaternion: <";
    oss << std::to_string(quaternion._w) << ", ";
    oss << std::to_string(quaternion._x) << "i, ";
    oss << std::to_string(quaternion._y) << "j, ";
    oss << std::to_string(quaternion._z) << "k>\n";

    glm::vec3 euler = quaternion.toEuler();

    oss << "Euler: (";
    oss << std::to_string(euler.x) << ", ";
    oss << std::to_string(euler.y) << ", ";
    oss << std::to_string(euler.z) << ")\n";

    return oss.str();
}

}; // namespace engine::math