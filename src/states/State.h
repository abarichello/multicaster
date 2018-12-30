#pragma once

#include <memory>

#include "../ResourceHolder.h"
#include "StateIDs.h"

class StateManager;

class State {
public:
    using Ptr = std::unique_ptr<State>;
    struct SharedContext {
        SharedContext(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);
        sf::RenderWindow* window;
        TextureHolder* textures;
        FontHolder* fonts;
    };

    State(StateManager& stateManager, SharedContext context);
    virtual ~State();

    virtual bool input(const sf::Event& event) = 0;
    virtual bool update(float delta) = 0;
    virtual void draw() = 0;

protected:
    void requestPush(StateType type);
    void requestPop();
    void requestClear();
    SharedContext context;

private:
    StateManager* stateManager;
};
