#include <iostream>

#include "util/Filepath.h"
#include "util/Lua.h"

void Lua::startLua(sol::state& lua) {
    lua.set_panic(sol::c_call<decltype(&panic), &panic>);
    lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::table, sol::lib::package);
    lua.require_file("lualog", Filepath::LUA_LOG);
}

void Lua::panic(sol::optional<std::string> maybeMsg) {
    std::cerr << "LUA PANIC";
    if (maybeMsg) {
        const std::string& msg = maybeMsg.value();
        std::cerr << " | Error: " << msg << std::endl;
    }
}

void Lua::startSave(sol::state& lua) {
    lua.script_file(Filepath::LUA_SAVE);
    lua["start_save"].call();
}
