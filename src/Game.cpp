#include "Game.h"
#include "GLOBAL.h"

Game::Game() : window(sf::VideoMode().getDesktopMode(), "multicaster", sf::Style::Fullscreen) {
    this->window.setFramerateLimit(Global::MAX_FRAMERATE);
    this->window.setVerticalSyncEnabled(true);

    this->circle.setRadius(100.0f);
    this->circle.setFillColor(sf::Color::Green);
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time delta = clock.restart();
        this->event();
        this->process(delta);
        this->draw();
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

void Game::process(sf::Time delta) {
}

void Game::draw() {
    window.clear(sf::Color::Black);
    window.draw(this->circle);
    window.display();
}
