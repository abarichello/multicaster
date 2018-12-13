#pragma once

#include "SFML/Graphics.hpp"

class Game {

public:
    Game();

    void Draw(sf::RenderWindow& window);

private:
    sf::CircleShape circle;
};
