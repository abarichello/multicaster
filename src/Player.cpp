#include <cmath>

#include "GLOBAL.h"
#include "Player.h"

Player::Player() {
    this->planeDistance = (screenWidth / 2) / std::tan(30);
    this->angleBetweenRays = Global::FOV / screenWidth;
}

Player::Player(sf::Vector2f startPosition) {
    Player();
    this->position = startPosition;
}

void Player::event() {
}

void Player::process(sf::Time delta) {
    for (int i = 0; i < screenWidth; i++) {
    }
}

void Player::draw(sf::RenderWindow& window) {
}
