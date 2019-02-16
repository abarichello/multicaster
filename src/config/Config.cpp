#include <fstream>
#include <iostream>

#include "config/Config.h"
#include "util/Filepath.h"

void Config::startup() {
    sol::state lua(sol::c_call<decltype(&panic), &panic>);
    lua.open_libraries(sol::lib::base, sol::lib::io);
    lua.require_file("lualog", Filepath::LUA_LOG);
    lua.do_file(Filepath::LUA_CONFIG);
    createConfigFile(lua);
}

void Config::createConfigFile(sol::state& lua) {
    sol::function startup = lua["startup"];
    startup.call();
}

void Config::panic(sol::optional<std::string> maybeMsg) {
    std::cerr << "LUA PANIC";
    if (maybeMsg) {
        const std::string& msg = maybeMsg.value();
        std::cerr << " | Error: " << msg << std::endl;
    }
}
