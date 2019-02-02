#include "MainMenuState.h"
#include "GLOBAL.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager& stateManager, SharedContext context)
    : State(stateManager, context), gui(*context.window) {
}

void MainMenuState::handleEvent(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) {
        return;
    }

    auto keyPressed = event.key.code;
    if (keyPressed == sf::Keyboard::Space || keyPressed == sf::Keyboard::Enter) {
        requestPop();
        requestPush(StateType::Game);
    }
    if (keyPressed == sf::Keyboard::Escape) {
        requestClear();
    }
    gui.handleEvent(event);
}

void MainMenuState::update(float delta) {
}

void MainMenuState::draw() {
    gui.draw();
}
