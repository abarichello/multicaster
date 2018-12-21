#include "Debug.h"
#include "GLOBAL.h"

Debug::Debug(sf::Vector2f textPosition) {
    debugFont.loadFromFile(Global::DEBUG_FONT_PATH);
    debugText.setFont(debugFont);
    debugText.setCharacterSize(35);
    debugText.setFillColor(sf::Color::White);
    debugText.setPosition(textPosition);
}

void Debug::setText(std::string& text) {
    debugText.setString(text);
}

void Debug::draw(sf::RenderWindow& window) {
    window.draw(debugText);
}
