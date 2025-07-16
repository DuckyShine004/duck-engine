#pragma once

namespace manager {

class Manager {
  public:
    Manager(const Manager &) = delete;

    Manager &operator=(const Manager &) = delete;

  protected:
    Manager();

    ~Manager();
};

} // namespace manager