#include "MainMenuState.h"
#include "GLOBAL.h"
#include "StateManager.h"
#include "network/Protocol.h"
#include "util/Savefile.h"

MainMenuState::MainMenuState(StateManager& stateManager, SharedContext context)
    : State(stateManager, context),
      gui(*context.window),
      hostButton(tgui::Button::create()),
      joinButton(tgui::Button::create()),
      spButton(tgui::Button::create()),
      ipAddrInput(tgui::EditBox::create()) {
    setupUI();
}

void MainMenuState::setupUI() {
    hostButton->setText("CREATE SERVER");
    hostButton->setSize(300, 70);
    hostButton->setPosition("&.width / 2 - width / 2", "&.height / 2 - height / 2");
    hostButton->connect("pressed", [this]() { buttonPressed(Button::Host); });
    gui.add(hostButton, "hostButton");

    ipAddrInput->setDefaultText("IP ADDRESS");
    Savefile save;
    auto lastIp = save.getSaveData<std::string>("last_ip");
    ipAddrInput->setText(lastIp);
    ipAddrInput->setSize(150, 35);
    ipAddrInput->setPosition("hostButton.left", bindTop(hostButton) + "hostButton.height" + 10);
    gui.add(ipAddrInput, "ipAddrInput");

    joinButton->setText("JOIN SERVER");
    joinButton->setSize(150, 35);
    joinButton->setPosition("ipAddrInput.right", "ipAddrInput.top");
    joinButton->connect("pressed", [this]() { buttonPressed(Button::Join); });
    gui.add(joinButton, "joinButton");

    spButton->setText("SINGLEPLAYER");
    spButton->setSize(300, 35);
    spButton->setPosition("hostButton.left", bindTop(joinButton) + "joinButton.height" + 10);
    spButton->connect("pressed", [this]() { buttonPressed(Button::Single); });
    gui.add(spButton, "spButton");
}

void MainMenuState::buttonPressed(Button button) {
    requestPop();
    switch (button) {
        case Button::Host:
            requestPush(StateType::HostMultiplayer);
            break;
        case Button::Join: {
            Savefile save;
            auto lastIp = ipAddrInput->getText();
            save.setSaveData<std::string>("last_ip", lastIp);
            requestPush(StateType::PeerMultiplayer);
            break;
        }
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
