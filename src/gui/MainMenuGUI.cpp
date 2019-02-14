#include "gui/MainMenuGUI.h"
#include "util/Filepath.h"

MainMenuGUI::MainMenuGUI(sf::RenderWindow& window) : gui(window) {
    this->window = &window;
}

void MainMenuGUI::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        gui.setView(window->getView());
    }

    gui.handleEvent(event);
}

void MainMenuGUI::draw() {
    gui.draw();
}
