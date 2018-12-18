#include <cmath>
#include <iostream>

#include "GLOBAL.h"
#include "Player.h"

Player::Player()
    : position(2.0f, 2.5f), direction(-1.0f, 0.0f), plane(0.65f, 0.0f), lines(sf::Lines, screenRes.width) {
}

Player::Player(sf::Vector2f startPosition) {
    Player();
    this->position = startPosition;
}

void Player::input(float delta) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    }
}

void Player::process(float delta) {
    this->input(delta);

    this->lines.clear();
    for (int i = 0; i < screenRes.width; ++i) {
        // Rays initial positions
        sf::Vector2f rayPos = this->position;
        sf::Vector2i worldPos(this->position);

        float cameraX = 2.0f * (float)i / (float)screenRes.width - 1.0f;
        sf::Vector2f rayDir = this->direction + this->plane * cameraX;
        sf::Vector2f deltaDist(std::sqrt(1.0f + (rayDir.y * rayDir.y) / (rayDir.x * rayDir.x)),
                               std::sqrt(1.0f + (rayDir.x * rayDir.x) / (rayDir.y * rayDir.y)));

        sf::Vector2i step;
        sf::Vector2f sideDist;
        if (rayDir.x < 0.0f) {
            step.x = -1;
            sideDist.x = (rayPos.x - worldPos.x) * deltaDist.x;
        } else {
            step.x = 1;
            sideDist.x = (worldPos.x + 1 - rayPos.x) * deltaDist.x;
        }

        if (rayDir.y < 0.0f) {
            step.y = -1;
            sideDist.y = (rayPos.y - worldPos.y) * deltaDist.y;
        } else {
            step.y = 1;
            sideDist.y = (worldPos.y + 1 - rayPos.y) * deltaDist.y;
        }

        // Cast rays until hitting a wall
        bool hit, horizontal;
        while (!hit) {
            if (sideDist.x < sideDist.y) {
                sideDist.x += deltaDist.x;
                worldPos.x += step.x;
                horizontal = true;
            } else {
                sideDist.y += deltaDist.y;
                worldPos.y += step.y;
                horizontal = false;
            }

            if (map[(int)worldPos.x][(int)worldPos.y] > 0) {
                hit = true;
            }
        }

        float perpWallDist = 0.0f;
        if (horizontal) {
            perpWallDist = std::fabs(((float)worldPos.x - rayPos.x + (1.0f - (float)step.x) / 2.0f) / rayDir.x);
        } else {
            perpWallDist = std::fabs(((float)worldPos.y - rayPos.y + (1.0f - (float)step.y) / 2.0f) / rayDir.y);
        }

        // Determine line height
        int lineHeight = std::abs(screenRes.height / perpWallDist);
        int drawStart = -lineHeight / 2 + screenRes.height / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }
        int drawEnd = lineHeight / 2 + screenRes.height / 2;
        if (drawEnd >= screenRes.height) {
            drawEnd = screenRes.height - 1;
        }

        // Draw columns
        this->lines.append(sf::Vertex(sf::Vector2f((float)i, (float)drawStart), sf::Color::Red));
        this->lines.append(sf::Vertex(sf::Vector2f((float)i, (float)drawEnd), sf::Color::Red));
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(lines);
}
