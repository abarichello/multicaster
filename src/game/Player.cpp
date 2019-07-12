#include <cmath>
#include <sstream>

#include "Player.h"
#include "util/Filepath.h"
#include "util/Math.h"

Player::Player(sf::Int32 playerID, sf::TcpSocket* socket)
    : position(playerStartPos),
      direction(0.0f, 1.0f),
      plane(-0.65f, 0.0f),
      lines(sf::Lines, screenRes.width),
      fps(),
      debug(sf::Vector2f(0.0f, 50.0f)),
      playerID(playerID),
      socket(socket),
      keymap(),
      map() {
}

Player::~Player() {
    delete socket;
}

void Player::handleEvent() {
    if (!focused) {
        return;
    }

    // MOVEMENT
    if (keymap.isKeyPressed(KeyMap::FORWARD)) {
        moveForward();
    }
    if (keymap.isKeyPressed(KeyMap::BACKWARD)) {
        moveBackward();
    }
    if (keymap.isKeyPressed(KeyMap::LEFT)) {
        moveLeft();
    }
    if (keymap.isKeyPressed(KeyMap::RIGHT)) {
        moveRight();
    }
    if (keymap.isKeyPressed(KeyMap::TURNLEFT)) {
        turnLeft();
    }
    if (keymap.isKeyPressed(KeyMap::TURNRIGHT)) {
        turnRight();
    }

    // ETC
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num0)) {
        position = playerStartPos;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tilde)) {
        this->debugMode = !debugMode;
    }
}

void Player::update(float delta) {
    this->delta = delta;
    handleEvent();

    if (debugMode) {
        std::stringstream s;
        s << "X: " << position.x << "\nY: " << position.y;
        auto msg = s.str();
        debug.setText(msg);
    }
    fps.update(delta);
}

void Player::raycast() {
    lines.clear();

    for (int i = 0; i < screenRes.width; ++i) {
        // Rays initial positions
        sf::Vector2f rayPos = position;
        sf::Vector2i worldPos(position);

        float cameraX = 2.0f * (float)i / (float)screenRes.width - 1.0f;
        sf::Vector2f rayDir = direction + plane * cameraX;
        sf::Vector2f deltaDist;
        deltaDist.x = std::abs(1.0f / rayDir.x);
        deltaDist.y = std::abs(1.0f / rayDir.y);

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

        // Cast rays using Digital Differential Analysis(DDA) until hitting a wall
        bool hit = false;
        bool horizontal = false;
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

            if (map.getTile(worldPos) > 0) {
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
        int lineHeight = (int)std::abs(screenRes.height / perpWallDist);
        int drawStart = -lineHeight / 2 + screenRes.height / 2;
        if (drawStart < 0) {
            drawStart = 0;
        }
        int drawEnd = lineHeight / 2 + screenRes.height / 2;
        if (drawEnd >= screenRes.height) {
            drawEnd = screenRes.height - 1;
        }

        sf::Color wallColor = sf::Color::Red;

        // Draw floor
        sf::Color floorColor;
        floorColor.r = wallColor.r / 5;
        floorColor.g = wallColor.g / 5;
        floorColor.b = wallColor.b / 5;

        float groundPixel = screenRes.height;
        lines.append(sf::Vertex(sf::Vector2f((float)i, groundPixel), floorColor));
        groundPixel = (lineHeight * plane.y + screenRes.height) * 0.5f;
        lines.append(sf::Vertex(sf::Vector2f((float)i, groundPixel), floorColor));

        // Draw ceiling
        sf::Color ceilingColor;
        ceilingColor.r = wallColor.r / 11;
        ceilingColor.g = wallColor.g / 11;
        ceilingColor.b = wallColor.b / 11;

        float ceilingPixel = 0.f;
        lines.append(sf::Vertex(sf::Vector2f((float)i, ceilingPixel), ceilingColor));
        ceilingPixel = (-lineHeight * 1.f - plane.y + screenRes.height) * 0.5f;
        lines.append(sf::Vertex(sf::Vector2f((float)i, ceilingPixel), ceilingColor));

        // Shadow horizontal walls
        if (horizontal) {
            wallColor.r /= 2;
            wallColor.g /= 2;
            wallColor.b /= 2;
        }

        // Append columns to VertexArray
        lines.append(sf::Vertex(sf::Vector2f((float)i, (float)drawStart), wallColor));
        lines.append(sf::Vertex(sf::Vector2f((float)i, (float)drawEnd), wallColor));
    }
}

void Player::draw(sf::RenderWindow& window) {
    raycast();
    window.draw(lines);
    map.drawMinimap(window);

    if (debugMode) {
        fps.draw(window);
        debug.draw(window);
    }
    focused = window.hasFocus();
}

void Player::moveForward() {
    float deltaMovement = direction.x * movementSpeed * delta;
    int x = int(position.x + deltaMovement);
    int y = int(position.y);
    if (map.getTile(sf::Vector2i(x, y)) == 0) {
        position.x += deltaMovement;
    }

    deltaMovement = direction.y * movementSpeed * delta;
    x = int(position.x);
    y = int(position.y + deltaMovement);
    if (map.getTile(sf::Vector2i(x, y)) == 0) {
        position.y += deltaMovement;
    }
}

void Player::moveBackward() {
    float deltaMovement = direction.x * movementSpeed * delta;
    int x = int(position.x - deltaMovement);
    int y = int(position.y);
    if (map.getTile(sf::Vector2i(x, y)) == 0) {
        position.x -= deltaMovement;
    }

    deltaMovement = direction.y * movementSpeed * delta;
    x = int(position.x);
    y = int(position.y - deltaMovement);
    if (map.getTile(sf::Vector2i(x, y)) == 0) {
        position.y -= deltaMovement;
    }
}

void Player::moveLeft() {
    float deltaMovement = plane.x * movementSpeed * delta;
    int x = int(position.x - deltaMovement);
    int y = int(position.y);
    if (map.getTile(sf::Vector2i(x, y)) == 0) {
        position.x -= deltaMovement;
    }

    deltaMovement = plane.y * movementSpeed * delta;
    x = int(position.x);
    y = int(position.y - deltaMovement);
    if (map.getTile(sf::Vector2i(x, y)) == 0) {
        position.y -= deltaMovement;
    }
}

void Player::moveRight() {
    float deltaMovement = plane.x * movementSpeed * delta;
    int x = int(position.x + deltaMovement);
    int y = int(position.y);
    if (map.getTile(sf::Vector2i(x, y)) == 0) {
        position.x += deltaMovement;
    }

    deltaMovement = plane.y * movementSpeed * delta;
    x = int(position.x);
    y = int(position.y + deltaMovement);
    if (map.getTile(sf::Vector2i(x, y)) == 0) {
        position.y += deltaMovement;
    }
}

void Player::turnLeft() {
    direction = Math::rotateVector(direction, -1.0f * turnSpeed * delta);
    plane = Math::rotateVector(plane, turnSpeed * delta * -1.0f);
}

void Player::turnRight() {
    direction = Math::rotateVector(direction, 1.0f * turnSpeed * delta);
    plane = Math::rotateVector(plane, turnSpeed * delta);
}
