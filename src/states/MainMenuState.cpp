#include "MainMenuState.h"
#include "../GLOBAL.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager& stateManager, SharedContext context)
    : State(stateManager, context) {
    menuText.setFont(context.fonts->get(Resources::MENU_FONT));
    menuText.setString("MAIN MENU");
    menuText.setCharacterSize(Global::resolution.width / 30);
    menuText.setPosition(100.0f, 100.0f);
}

bool MainMenuState::input(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) {
        return false;
    }

    auto keyPressed = event.key.code;
    if (keyPressed == sf::Keyboard::Space || keyPressed == sf::Keyboard::Enter) {
        requestPop();
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
    sf::RenderWindow& window = *context.window;
    window.draw(menuText);
}
