#include <SFML/Graphics.hpp>

#include "GLOBAL.h"
#include "config/Config.h"
#include "game/Game.h"

int main() {
    Game game;
    Config::startup();
    game.run();
    return 0;
}
