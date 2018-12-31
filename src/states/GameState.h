#pragma once

#include "../game/Player.h"
#include "State.h"
#include "StateManager.h"

class GameState : public State {
public:
    GameState(StateManager& stateManager, SharedContext context);

    virtual bool input(const sf::Event& event);
    virtual bool update(float delta);
    virtual void draw();

private:
    Player player1;
};
