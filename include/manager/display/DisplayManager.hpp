#pragma once

#include "manager/Manager.hpp"

namespace manager::display {

struct Resolution {
    int width;
    int height;
};

class DisplayManager final : public Manager {
  public:
    static DisplayManager &getInstance();

    int getWidth();

    int getHeight();

    void setWidth(int width);

    void setHeight(int height);

    float getAspectRatio();

    void updateResolution(int width, int height);

  private:
    DisplayManager();

    ~DisplayManager();

    Resolution _resolution;
};

} // namespace manager::display