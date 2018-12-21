#include "Debug.h"
#include "GLOBAL.h"

Debug::Debug() {
    debugFont.loadFromFile(Global::DEBUG_FONT_PATH);
    fpsText.setFont(debugFont);
    fpsText.setCharacterSize(35);
    fpsText.setFillColor(sf::Color::White);
}

void Debug::setText(std::string text) {
    fpsText.setString(text);
}

void Debug::draw(sf::RenderWindow& window) {
    window.draw(fpsText);
}
