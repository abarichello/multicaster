#include "Game.h"
#include "GLOBAL.h"

Game::Game()
    : window(sf::VideoMode().getDesktopMode(), "multicaster", sf::Style::Fullscreen), stateManager(context), player1() {
    window.setFramerateLimit(Global::MAX_FRAMERATE);
    window.setVerticalSyncEnabled(true);

    context.window = &window;
    stateManager.switchTo(StateType::MainMenu);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        event();
        process(delta);
        draw();
    }
}

void Game::event() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                break;
        }
    }
}

void Game::process(float delta) {
    player1.process(delta);
    stateManager.update(delta);
}

void Game::draw() {
    window.clear(sf::Color::Black);
    stateManager.draw();
    window.display();
}

void Game::lateUpdate() {
    stateManager.queueFree();
}
