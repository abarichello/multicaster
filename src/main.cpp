#include <SFML/Graphics.hpp>
#include <sol.hpp>

#include "GLOBAL.h"
#include "config/Config.h"
#include "game/Game.h"
#include "util/Lua.h"
#include "util/Savefile.h"

int main() {
    puts("");

    sol::state lua = Lua::startLua();
    Savefile::startSave(lua);

    Game game;
    game.run();
    return 0;
}
