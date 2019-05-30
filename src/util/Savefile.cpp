#include "util/Savefile.h"
#include "util/Filepath.h"
#include "util/Lua.h"

Savefile::Savefile() {
    saveLuaState = Lua::startLua();
    saveLuaState.script_file(Filepath::LUA_SAVE);
    saveLuaState["start_save"].call();
}

void Savefile::loadSaveFile() {
    saveLuaState["load_save_file"].call();
}

void Savefile::writeSaveFile() {
    saveLuaState["write_save_file"].call();
}
