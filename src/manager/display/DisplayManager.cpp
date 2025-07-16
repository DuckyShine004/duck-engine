#include "manager/display/DisplayManager.hpp"

namespace manager::display {

DisplayManager::DisplayManager() = default;

DisplayManager::~DisplayManager() = default;

DisplayManager &DisplayManager::getInstance() {
    static DisplayManager instance;

    return instance;
}

int DisplayManager::getWidth() {
    return this->_resolution.width;
}

int DisplayManager::getHeight() {
    return this->_resolution.height;
}

void DisplayManager::setWidth(int width) {
    this->_resolution.width = width;
}

void DisplayManager::setHeight(int height) {
    this->_resolution.height = height;
}

float DisplayManager::getAspectRatio() {
    return (float)this->_resolution.width / this->_resolution.height;
}

void DisplayManager::updateResolution(int width, int height) {
    this->_resolution.width = width;
    this->_resolution.height = height;
}

} // namespace manager::display
