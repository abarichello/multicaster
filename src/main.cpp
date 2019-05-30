#include <SFML/Graphics.hpp>
#include <sol.hpp>
#include <string>

#include "GLOBAL.h"
#include "config/Config.h"
#include "game/Game.h"
#include "util/Lua.h"
#include "util/Savefile.h"

int main() {
    puts("");

    Savefile save;

    Game game;
    game.run();
    return 0;
}
