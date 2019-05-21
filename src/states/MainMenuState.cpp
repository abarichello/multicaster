#include "MainMenuState.h"
#include "GLOBAL.h"
#include "StateManager.h"

MainMenuState::MainMenuState(StateManager& stateManager, SharedContext context)
    : State(stateManager, context), gui(*context.window) {
    setupUI();
}

void MainMenuState::setupUI() {
    hostButton = tgui::Button::create("CREATE SERVER");
    hostButton->setSize(300, 70);
    hostButton->setPosition("&.width / 2 - width / 2", "&.height / 2 - height / 2");
    gui.add(hostButton, "hostButton");
    hostButton->connect("pressed", [this]() { buttonPressed(Button::Host); });

    joinButton = tgui::Button::create("JOIN SERVER");
    joinButton->setSize(300, 70);
    joinButton->setPosition("hostButton.left", bindTop(hostButton) + "height" + 10);
    gui.add(joinButton, "joinButton");
    joinButton->connect("pressed", [this]() { buttonPressed(Button::Join); });

    spButton = tgui::Button::create("SINGLEPLAYER");
    spButton->setSize(300, 35);
    spButton->setPosition("hostButton.left", bindTop(joinButton) + "joinButton.height" + 10);
    gui.add(spButton, "spButton");
    spButton->connect("pressed", [this]() { buttonPressed(Button::Single); });
}

void MainMenuState::buttonPressed(Button button) {
    requestPop();
    switch (button) {
        case Button::Host:
            requestPush(StateType::HostMultiplayer);
            break;
        case Button::Join:
            requestPush(StateType::PeerMultiplayer);
            break;
        case Button::Single:
            requestPush(StateType::SingleplayerGame);
            break;
    }
}

void MainMenuState::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::Resized) {
        gui.setView(context.window->getView());
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        requestClear();
    }
    gui.handleEvent(event);
}

void MainMenuState::update(float delta) {
}

void MainMenuState::draw() {
    gui.draw();
}
