#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Debug {
public:
    Debug(sf::Vector2f textPosition = sf::Vector2f(0.0f, 0.0f));

    void setText(std::string& text);
    void draw(sf::RenderWindow& window);

protected:
    sf::Font debugFont;
    sf::Text debugText;
};
