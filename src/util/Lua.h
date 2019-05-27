#pragma once

#include <sol.hpp>

namespace Lua {
    void startLua(sol::state& lua);
    void panic(sol::optional<std::string> maybeMsg);

    void startSave(sol::state& lua);
}  // namespace Lua
