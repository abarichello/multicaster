#pragma once

#include "State.h"
#include "StateManager.h"

class PauseState : public State {
public:
    PauseState(StateManager& stateManager, SharedContext context);

    virtual void handleEvent(const sf::Event& event);
    virtual void update(float delta);
    virtual void draw();

private:
    sf::RectangleShape mask;
    sf::Font pauseFont;
    sf::Text pauseText;
};
