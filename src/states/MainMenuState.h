#pragma once

#include "State.h"
#include "StateManager.h"
#include "util/ResourceHolder.h"

class MainMenuState : public State {
public:
    MainMenuState(StateManager& stateManager, SharedContext context);

    virtual void handleEvent(const sf::Event& event);
    virtual void update(float delta);
    virtual void draw();

private:
    tgui::Gui gui;
};
