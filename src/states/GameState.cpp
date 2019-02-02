#include "GameState.h"
#include "GLOBAL.h"

GameState::GameState(StateManager& stateManager, SharedContext context) : State(stateManager, context) {
}

void GameState::handleEvent(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Escape) {
        requestPop();
        requestPush(StateType::MainMenu);
    }
}

void GameState::update(float delta) {
    player1.update(delta);
}

void GameState::draw() {
    sf::RenderWindow& window = *context.window;
    player1.draw(window);
}
