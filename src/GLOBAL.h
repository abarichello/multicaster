#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace Global {
    const int MAX_FRAMERATE = 165;
    const int FOV = 65;
    const int ATLAS_SIZE = 512;
    const int TEXTURE_SIZE = 128;

    const sf::VideoMode resolution = sf::VideoMode().getDesktopMode();

    const std::string DEBUG_FONT_PATH = "./resources/fonts/debugfont.ttf";
    const std::string MENU_FONT_PATH = "./resources/fonts/menufont.ttf";
}  // namespace Global
