#pragma once

#include <sol.hpp>

namespace Config {
    void startup();
    void createConfigFile(sol::state& lua);
    void panic(sol::optional<std::string> maybeMsg);
};  // namespace Config
