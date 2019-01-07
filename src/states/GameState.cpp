#include "GameState.h"
#include "GLOBAL.h"

GameState::GameState(StateManager& stateManager, SharedContext context) : State(stateManager, context) {
}

bool GameState::input(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Escape) {
        context.window->close();
    }
    return true;
}

bool GameState::update(float delta) {
    player1.update(delta);
    return true;
}

void GameState::draw() {
    player1.draw(*context.window);
}
