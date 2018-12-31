#pragma once

#include "../util/ResourceHolder.h"
#include "State.h"
#include "StateManager.h"

class MainMenuState : public State {
public:
    MainMenuState(StateManager& stateManager, SharedContext context);

    virtual bool input(const sf::Event& event);
    virtual bool update(float delta);
    virtual void draw();

private:
    FontHolder fonts;
    sf::Font fontss;
    sf::Text menuText;
};
