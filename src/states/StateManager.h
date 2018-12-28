#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <functional>
#include <unordered_map>

#include "State.h"

enum class StateType {
    MainMenu,
    Game,
};

using StateFactory = std::unordered_map<StateType, std::function<State::Ptr()>>;

class StateManager : private sf::NonCopyable {
public:
    enum Action {
        Push,
        Pop,
        Clear,
    };

    explicit StateManager(State::SharedContext sharedContext);
    ~StateManager();

    void update(float delta);
    void input(const sf::Event& event);
    void draw();

    void push(StateType type);
    void pop();
    void clear();
    bool isEmpty();

    void applyPendingChanges();

private:
    struct PendingChange {
        Action action;
        StateType type;
    };

    template <typename T>
    void registerState(const StateType type);
    State::Ptr createState(const StateType type);

    std::vector<State::Ptr> states;
    std::vector<PendingChange> pending;
    State::SharedContext* context;
    StateFactory stateFactory;
};
