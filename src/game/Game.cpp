#include "Game.h"
#include "../GLOBAL.h"
#include "../states/MainMenuState.h"
#include "../states/State.h"

Game::Game()
    : window(sf::VideoMode().getDesktopMode(), "multicaster", sf::Style::Fullscreen),
      stateManager(State::SharedContext(window, textures, fonts)),
      player1() {
    window.setFramerateLimit(Global::MAX_FRAMERATE);
    window.setVerticalSyncEnabled(true);

    loadResources();

    stateManager.registerState<MainMenuState>(StateType::MainMenu);
    stateManager.push(StateType::MainMenu);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        event();
        process(delta);
        draw();

        if (stateManager.isEmpty()) {
            window.close();
        }
    }
}

void Game::event() {
    sf::Event event;
    while (window.pollEvent(event)) {
        stateManager.input(event);
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }
}

void Game::process(float delta) {
    stateManager.update(delta);
}

void Game::draw() {
    window.clear(sf::Color::Black);
    stateManager.draw();
    window.display();
}

void Game::loadResources() {
    fonts.load(Resources::DEBUG_FONT, Global::DEBUG_FONT_PATH);
    fonts.load(Resources::MENU_FONT, Global::MENU_FONT_PATH);
}
