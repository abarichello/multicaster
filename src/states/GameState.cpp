#include "GameState.h"
#include "GLOBAL.h"

GameState::GameState(StateManager& stateManager, SharedContext context)
    : State(stateManager, context), player(1, nullptr) {
}

void GameState::handleEvent(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Escape) {
        requestPop();
        requestPush(StateType::MainMenu);
    }
}

void GameState::update(float delta) {
    player.update(delta);
}

void GameState::draw() {
    sf::RenderWindow& window = *context.window;
    player.draw(window);
}
