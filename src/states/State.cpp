#include "State.h"
#include "StateManager.h"

State::SharedContext::SharedContext(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
    : window(&window), textures(&textures), fonts(&fonts) {
}

State::State(StateManager& stateManager, SharedContext context)
    : stateManager(&stateManager), context(context), gui(*context.window) {
}

State::~State() {
}

void State::requestPush(StateType type) {
    stateManager->push(type);
}

void State::requestPop() {
    stateManager->pop();
}

void State::requestClear() {
    stateManager->clear();
}
