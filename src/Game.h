#pragma once

#include "SFML/Graphics.hpp"

class Game {
public:
    Game();

    void run();

private:
    void event();
    void process(sf::Time delta);
    void draw();

    sf::RenderWindow window;
    sf::CircleShape circle;
};
