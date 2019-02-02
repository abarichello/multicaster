#include "PauseState.h"
#include "GLOBAL.h"
#include "util/Filepath.h"

PauseState::PauseState(StateManager& stateManager, SharedContext context)
    : State(stateManager, context), mask(sf::Vector2f(context.window->getSize())) {
    mask.setFillColor(sf::Color(0, 0, 0, 154));
    pauseFont.loadFromFile(Filepath::MENU_FONT);

    pauseText.setFont(pauseFont);
    pauseText.setString("PAUSED");
    pauseText.setCharacterSize(100);
    sf::Vector2f posiiton = sf::Vector2f((float)Global::resolution.width / 2, (float)Global::resolution.height / 2);
    pauseText.setPosition(posiiton);
}

void PauseState::handleEvent(const sf::Event& event) {
    if (event.key.code == sf::Keyboard::Escape) {
        requestPop();
        return;
    }
    if (event.key.code == sf::Keyboard::Q) {
        context.window->close();
    }
}

void PauseState::update(float delta) {
    return;
}

void PauseState::draw() {
    sf::RenderWindow& window = *context.window;
    window.draw(mask);
    window.draw(pauseText);
}
