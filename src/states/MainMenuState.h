#pragma once

#include "State.h"
#include "StateManager.h"
#include "util/ResourceHolder.h"

class MainMenuState : public State {
public:
    MainMenuState(StateManager& stateManager, SharedContext context);

    virtual bool handleEvent(const sf::Event& event);
    virtual bool update(float delta);
    virtual void draw();

private:
    FontHolder fonts;
    sf::Font fontss;
    sf::Text menuText;
};
