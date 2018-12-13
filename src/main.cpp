#include <SFML/Graphics.hpp>

#include "GLOBAL.h"
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode().getDesktopMode(), "multicaster", sf::Style::Fullscreen);
    window.setFramerateLimit(Global::MAX_FRAMERATE);
    window.setVerticalSyncEnabled(true);
    Game game;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    break;
                default:
                    break;
            }

            window.clear(sf::Color::Black);
            game.Draw(window);
            window.display();
        }
    }

    return 0;
}
