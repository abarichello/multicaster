#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "GLOBAL.h"
#include "Map.h"
#include "gui/Debug.h"
#include "gui/FPS.h"
#include "input/KeyMap.h"

class Player {
public:
    Player(sf::Int32 playerID, sf::TcpSocket* socket);
    ~Player();

    void handleEvent();
    void update(float delta);
    void raycast();
    void draw(sf::RenderWindow& window);

    sf::Vector2f position;

private:
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    void turnLeft();
    void turnRight();

    KeyMap keymap;
    sf::VideoMode screenRes = Global::resolution;
    sf::VertexArray columns;
    sf::Vector2f direction;
    sf::Vector2f plane;
    sf::VertexArray lines;

    float movementSpeed = 4.0f;
    float turnSpeed = 1.7f;
    float delta = 0.0f;

    sf::TcpSocket* socket;
    sf::Int32 playerID;
    Map map;

    Debug debug;
    FPS fps;
    bool debugMode = true;
};
