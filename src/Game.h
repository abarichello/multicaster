#pragma once

#include "SFML/Graphics.hpp"

#include "FPS.h"
#include "Player.h"
#include "states/StateManager.h"

class Game {
public:
    Game();

    void run();

private:
    void event();
    void process(float delta);
    void draw();
    void lateUpdate();

    sf::RenderWindow window;
    Player player1;
    StateManager stateManager;
    State::SharedContext context;
};
