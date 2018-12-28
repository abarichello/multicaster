#include "StateManager.h"

StateManager::StateManager(State::SharedContext context) : context(&context) {
    // registerState<>(StateType::MainMenu);
    // registerState<>(StateType::Game);
}

StateManager::~StateManager() {
    for (auto& itr : states) {
        itr->destroy();
    }
}

void StateManager::update(float delta) {
    for (auto itr = states.begin(); itr != states.end(); ++itr) {
        if (!(*itr)->update(delta)) {
            return;
        }
    }
}
void StateManager::input(const sf::Event& event) {
    for (auto itr = states.begin(); itr != states.end(); ++itr) {
        if (!(*itr)->input(event)) {
            return;
        }
    }
}

void StateManager::draw() {
    for (auto itr = states.end(); itr != states.begin(); --itr) {
        (*itr)->draw();
    }
}

bool StateManager::isEmpty() {
    return states.empty();
}

void StateManager::applyPendingChanges() {
    for (PendingChange change : pending) {
        switch (change.action) {
            case Push:
                states.push_back(createState(change.type));
                break;
            case Pop:
                states.pop_back();
            case Clear:
                states.clear();
                break;
        }
    }
}

template <typename T>
void StateManager::registerState(const StateType type) {
    stateFactory[type] = [this]() { return State::Ptr(new T(*this, context)); };
}

State::Ptr StateManager::createState(const StateType type) {
    auto found = stateFactory.find(type);
    assert(found != stateFactory.end());
    return found->second();
}
