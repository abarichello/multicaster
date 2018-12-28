#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include <unordered_map>

#include "State.h"

enum class StateType {
    MainMenu,
    Game,
};

using StateFactory = std::unordered_map<StateType, std::function<State*(void)>>;

class StateManager : private sf::NonCopyable {
public:
    explicit StateManager(State::SharedContext sharedContext);
    ~StateManager();

    void update(float delta);
    void draw();

    bool hasState(const StateType type);
    void switchTo(const StateType type);
    void remove(const StateType type);

    void queueFree();
    bool isEmpty();

private:
    void createState(const StateType type);
    void removeState(const StateType type);

    template <typename T>
    void registerState(const StateType type);

    State::SharedContext* context;
    std::vector<std::pair<StateType, State*>> states;
    std::vector<StateType> removeQueue;
    StateFactory stateFactory;
};
