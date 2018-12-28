#pragma once

#include <memory>

class StateManager;

class State {
public:
    using Ptr = std::unique_ptr<State>;
    struct SharedContext {
        sf::RenderWindow* window;
    };

    State(StateManager& stateManager, SharedContext context);
    virtual ~State();

    virtual void ready() = 0;
    virtual void destroy() = 0;

    virtual void update(float delta) = 0;
    virtual void input(const sf::Event& event) = 0;
    virtual void draw() = 0;

private:
    StateManager* stateManager;
    SharedContext context;
};
