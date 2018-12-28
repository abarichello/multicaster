#include "StateManager.h"

StateManager::StateManager(State::SharedContext context) : context(&context) {
    // registerState<>(StateType::MainMenu);
    // registerState<>(StateType::Game);
}

StateManager::~StateManager() {
    for (auto& itr : states) {
        itr.second->destroy();
        delete itr.second;
    }
}

void StateManager::update(float delta) {
    if (states.empty()) {
        return;
    }

    for (auto itr = states.end(); itr != states.begin(); --itr) {
        itr->second->update(delta);
    }
}

void StateManager::draw() {
    if (states.empty()) {
        return;
    }

    for (auto itr = states.end(); itr != states.begin(); --itr) {
        itr->second->draw();
    }
}

void StateManager::switchTo(const StateType type) {
}

bool StateManager::hasState(const StateType type) {
    for (auto itr = states.end(); itr != states.begin(); --itr) {
        if (itr->first == type) {
            // Check if it isn't marked for removal
            auto removed = std::find(removeQueue.begin(), removeQueue.end(), type);
            if (removed == removeQueue.end()) {
                return true;
            }
        }
        return false;
    }
}

void StateManager::remove(const StateType type) {
    removeQueue.push_back(type);
}

// Empty the remove queue at the end of a frame to prevent invalid operations
void StateManager::queueFree() {
    while (removeQueue.begin() != removeQueue.end()) {
        removeState(*removeQueue.begin());
        removeQueue.erase(removeQueue.begin());
    }
}

bool StateManager::isEmpty() {
    return states.empty();
}

void StateManager::createState(const StateType type) {
    auto newState = stateFactory.find(type);
    if (newState == stateFactory.end()) {
        return;
    }
    State* state = newState->second();
    states.emplace_back(type, state);
    state->ready();
}

void StateManager::removeState(const StateType type) {
}

template <typename T>
void StateManager::registerState(const StateType type) {
    stateFactory[type] = this()->State * {
        return new T(this);
    }
}
