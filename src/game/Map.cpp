#include "Map.h"

Map::Map() {
}

int Map::getTile(sf::Vector2i position) {
    if (position.x > mapWidth || position.y > mapHeight) {
        return -1;
    }

    return map[position.x][position.y];
}

sf::Vector2i Map::getMapSize() {
    return sf::Vector2i(mapWidth, mapHeight);
}
