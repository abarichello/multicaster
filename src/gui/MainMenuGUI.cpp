#include "gui/MainMenuGUI.h"
#include "util/Filepath.h"

MainMenuGUI::MainMenuGUI(sf::RenderWindow& window) : gui(window) {
}

void MainMenuGUI::handleEvent(const sf::Event& event) {
    gui.handleEvent(event);
}

void MainMenuGUI::draw() {
    gui.draw();
}
