#pragma once

#include <SFML/Graphics.hpp>

#include "../gui/FPS.h"
#include "../states/StateManager.h"
#include "../util/ResourceHolder.h"

class Game {
public:
    Game();

    void run();

private:
    void event();
    void update(float delta);
    void draw();

    void loadResources();
    void registerStates();

    sf::RenderWindow window;
    StateManager stateManager;
    TextureHolder textures;
    FontHolder fonts;
};
