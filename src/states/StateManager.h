#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <functional>
#include <map>

#include "State.h"
#include "StateType.h"

using StateFactory = std::map<StateType, std::function<State::Ptr()>>;

class StateManager : private sf::NonCopyable {
public:
    enum Action {
        Push,
        Pop,
        Clear,
    };

    explicit StateManager(State::SharedContext sharedContext);
    ~StateManager();

    void handleEvent(const sf::Event& event);
    void update(float delta);
    void draw();

    void push(StateType type);
    void pop();
    void clear();
    bool isEmpty() const;
    void applyPendingChanges();

    template <typename T>
    void registerState(StateType type);

private:
    struct PendingChange {
        PendingChange(Action action, StateType type = StateType::None);
        Action action;
        StateType type;
    };

    State::Ptr createState(const StateType type);

    std::vector<State::Ptr> states;
    std::vector<PendingChange> pendingList;
    State::SharedContext context;
    StateFactory stateFactory;
};

template <typename T>
void StateManager::registerState(StateType type) {
    stateFactory[type] = [this]() {
        auto ptr = State::Ptr(new T(*this, context));
        return ptr;
    };
}
