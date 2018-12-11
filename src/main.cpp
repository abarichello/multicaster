#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1366, 768), "multicaster");
    sf::CircleShape circle(100.0f);
    circle.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            window.clear(sf::Color::Black);
            window.draw(circle);
            window.display();
        }
    }

    return 0;
}
