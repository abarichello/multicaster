#pragma once

#include <SFML/Graphics.hpp>
#include <string>

namespace Global {
    const int MAX_FRAMERATE = 165;
    const int TEXTURE_SIZE = 256;  // Size of each individual texture
    const int ATLAS_SIZE = 1024;   // Size of the atlas (group of textures)

    const sf::VideoMode resolution = sf::VideoMode().getDesktopMode();
}  // namespace Global
