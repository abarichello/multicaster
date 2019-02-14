#pragma once

#include "TGUI/TGUI.hpp"

class MainMenuGUI {
public:
    MainMenuGUI(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event);
    void draw();

private:
    sf::RenderWindow* window;
    tgui::Gui gui;
};
