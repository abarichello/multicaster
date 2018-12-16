#pragma once

#include "SFML/Graphics.hpp"

#include "Player.h"

class Game {
public:
    Game();

    void run();

private:
    void event();
    void process(sf::Time delta);
    void draw();

    sf::RenderWindow window;
    Player player1;
};
