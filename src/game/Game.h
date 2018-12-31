#pragma once

#include <SFML/Graphics.hpp>

#include "../gui/FPS.h"
#include "../states/StateManager.h"
#include "../util/ResourceHolder.h"
#include "Player.h"

class Game {
public:
    Game();

    void run();

private:
    void event();
    void process(float delta);
    void draw();

    void loadResources();

    sf::RenderWindow window;
    StateManager stateManager;
    TextureHolder textures;
    FontHolder fonts;
    Player player1;
};
