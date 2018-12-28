#include "MainMenuState.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager& stateManager, SharedContext context)
    : State(stateManager, context) {
}

bool MainMenuState::input(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) {
        return false;
    }

    auto keyPressed = event.key.code;
    if (keyPressed == sf::Keyboard::Space || keyPressed == sf::Keyboard::Enter) {
        requestPush(StateType::Game);
    }
    if (keyPressed == sf::Keyboard::Escape) {
        requestClear();
    }
    return true;
}

bool MainMenuState::update(float delta) {
    return true;
}

void MainMenuState::draw() {
}
