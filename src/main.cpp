#include "application/Application.hpp"

#include "engine/sound/SoundPlayer.hpp"

using namespace engine::sound;

using namespace application;

int main() {
    SoundPlayer::getInstance();

    Application application;

    application.initialise();

    application.load();

    application.run();

    return 0;
}
