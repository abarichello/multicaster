#include <SFML/Graphics.hpp>

#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1366, 768), "multicaster");
    Game game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            window.clear(sf::Color::Black);
            game.Draw(window);
            window.display();
        }
    }

    return 0;
}
