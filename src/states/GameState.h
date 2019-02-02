#pragma once

#include "State.h"
#include "StateManager.h"
#include "game/Player.h"

class GameState : public State {
public:
    GameState(StateManager& stateManager, SharedContext context);

    virtual void handleEvent(const sf::Event& event);
    virtual void update(float delta);
    virtual void draw();

private:
    Player player1;
};
