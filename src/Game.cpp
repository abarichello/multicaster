#include "Game.h"

Game::Game() {
    this->circle.setRadius(100.0f);
    this->circle.setFillColor(sf::Color::Green);
}

void Game::Draw(sf::RenderWindow& window) {
    window.draw(this->circle);
}
