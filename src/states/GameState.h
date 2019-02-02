#pragma once

#include "State.h"
#include "StateManager.h"
#include "game/Player.h"

class GameState : public State {
public:
    GameState(StateManager& stateManager, SharedContext context);

    virtual bool handleEvent(const sf::Event& event);
    virtual bool update(float delta);
    virtual void draw();

private:
    Player player1;
};
