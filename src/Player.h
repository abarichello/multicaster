#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    Player(sf::Vector2f startPosition);

    void event();
    void process(sf::Time delta);
    void draw(sf::RenderWindow& window);

    sf::Vector2f position;

private:
    int screenWidth = sf::VideoMode().getDesktopMode().width;
    int planeDistance;
    int angleBetweenRays;

    const int PLAYER_HEIGHT = 32;
};
