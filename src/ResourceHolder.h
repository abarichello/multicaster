#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>

namespace Resources {
    enum ID {
        DEBUG_FONT = 0,
        MENU_FONT = 1,
    };
};  // namespace Resources

template <typename Resource>
class ResourceHolder {
public:
    void load(Resources::ID id, const std::string& path);
    Resource& get(Resources::ID id);

private:
    std::map<int, std::unique_ptr<Resource>> resourceMap;
};

typedef ResourceHolder<sf::Texture> TextureHolder;
typedef ResourceHolder<sf::Font> FontHolder;

template <typename Resource>
void ResourceHolder<Resource>::load(Resources::ID id, const std::string& path) {
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(path)) {
        std::cerr << "Error loading resource " << id << " from path: " << path;
        exit(-1);
    }

    auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template <typename Resource>
Resource& ResourceHolder<Resource>::get(Resources::ID id) {
    auto found = resourceMap.find(id);
    assert(found != resourceMap.end());
    return *found->second;
}
