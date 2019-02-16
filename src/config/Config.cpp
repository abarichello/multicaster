#include <fstream>
#include <iostream>

#include "config/Config.h"
#include "util/Filepath.h"

void Config::startup() {
    sol::state lua(sol::c_call<decltype(&panic), &panic>);
    lua.open_libraries(sol::lib::base, sol::lib::io);

    // Equivalent to 'local lualog = require "log"' in Lua code
    std::ifstream lualogFile(Filepath::LUA_LOG);
    std::stringstream stream;
    stream << lualogFile.rdbuf();
    std::string contents = stream.str();

    lua.require_script("lualog", contents);
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