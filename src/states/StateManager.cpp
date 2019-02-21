#include "StateManager.h"
#include "MainMenuState.h"

StateManager::StateManager(State::SharedContext context)
    : states(), pendingList(), context(context), stateFactory() {
}

StateManager::~StateManager() {
}

void StateManager::handleEvent(const sf::Event& event) {
    for (auto itr = states.rbegin(); itr != states.rend(); ++itr) {
        (*itr)->handleEvent(event);
    }
}

void StateManager::update(float delta) {
    for (auto itr = states.rbegin(); itr != states.rend(); ++itr) {
        (*itr)->update(delta);
    }
    applyPendingChanges();
}

void StateManager::draw() {
    for (State::Ptr& state : states) {
        state->draw();
    }
}

void StateManager::push(StateType type) {
    pendingList.push_back(PendingChange{Action::Push, type});
}

void StateManager::pop() {
    pendingList.push_back(PendingChange{Action::Pop});
}

void StateManager::clear() {
    pendingList.push_back(PendingChange{Action::Clear});
}

bool StateManager::isEmpty() const {
    return states.empty();
}

int StateManager::size() const {
    return states.size();
}

// Apply changes to the stack at the end of frame
void StateManager::applyPendingChanges() {
    for (PendingChange change : pendingList) {
        switch (change.action) {
            case Push:
                states.push_back(createState(change.type));
                break;
            case Pop:
                states.pop_back();
                break;
            case Clear:
                states.clear();
                break;
        }
    }
    pendingList.clear();
}

State::Ptr StateManager::createState(const StateType type) {
    auto found = stateFactory.find(type);
    assert(found != stateFactory.end());
    return found->second();
}

StateManager::PendingChange::PendingChange(Action action, StateType type) : action(action), type(type) {
}
