#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>

namespace Resources {
    enum ID {
        DEBUG_FONT = 0,
    };
};

template <typename Resource>
class ResourceHolder {
public:
    void load(Resources::ID id, const std::string& path);
    Resource& get(Resources::ID id);

private:
    std::map<int, std::unique_ptr<Resource>> resourceMap;
};
