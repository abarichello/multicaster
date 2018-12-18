#pragma once

#include "SFML/Graphics.hpp"

#include "Player.h"

class Game {
public:
    Game();

    void run();

private:
    void event();
    void process(float delta);
    void draw();

    sf::RenderWindow window;
    Player player1;
};
