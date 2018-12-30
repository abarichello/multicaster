#include "ResourceHolder.h"

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
