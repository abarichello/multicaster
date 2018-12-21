#include <SFML/Graphics.hpp>

#include <string>

class Debug {
public:
    Debug();

    void setText(std::string text);
    void draw(sf::RenderWindow& window);

private:
    sf::Font debugFont;
    sf::Text fpsText;
};
