#include "util/Savefile.h"
#include "util/Filepath.h"

void Savefile::startSave(sol::state& lua) {
    lua.script_file(Filepath::LUA_SAVE);
    lua["start_save"].call();
}
