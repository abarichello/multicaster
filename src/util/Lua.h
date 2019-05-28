#pragma once

#include <sol.hpp>

namespace Lua {
    sol::state startLua();
    void panic(sol::optional<std::string> maybeMsg);
}  // namespace Lua
