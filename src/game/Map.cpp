#include <cstdio>
#include <iostream>

#include "GLOBAL.h"
#include "Map.h"

Map::Map() {
    loadMinimap();
}

// Get tile identifier from map arrays
int Map::getTile(sf::Vector2i position) {
    if (position.x > mapSize.x || position.y > mapSize.y) {
        return -1;
    }
    return map[position.x][position.y];
}

// Get color representation to be used in minimap
sf::Color Map::getColor(sf::Vector2i position) {
    switch (getTile(position)) {
        case 0:
            return background;
        case 1:
            return border;
        default:
            return sf::Color::Magenta;
    }
}

// Generate minimap sprite
void Map::loadMinimap() {
    image.create(mapSize.x, mapSize.y, background);
    for (int i = 0; i < mapSize.x; ++i) {
        for (int j = 0; j < mapSize.y; ++j) {
            sf::Color color = getColor(sf::Vector2i(i, j));
            image.setPixel(i, j, color);
        }
    }

    sf::Texture tex;
    tex.loadFromImage(image);
    texture = tex;
    minimap.setTexture(texture);
    minimap.setPosition(minimapPos);
    minimap.setSize(tgui::Vector2f(minimapSize, minimapSize));

    saveMinimapToDisk(minimapPath);
}

void Map::drawMinimap(sf::RenderWindow& window) {
    minimap.draw(window, sf::RenderStates::Default);
}

// Save minimap as a image to disk
void Map::saveMinimapToDisk(const std::string& path) {
    if (!std::remove(path.c_str())) {
        std::cerr << "Failed while removing minimap" << std::endl;
    }
    if (!image.saveToFile(path)) {
        std::cerr << "Failed while saving minimap image" << std::endl;
    }
}
