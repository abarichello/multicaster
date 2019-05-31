#pragma once

#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/EditBox.hpp>

#include "State.h"
#include "StateManager.h"
#include "util/ResourceHolder.h"

class MainMenuState : public State {
public:
    MainMenuState(StateManager& stateManager, SharedContext context);

    enum class Button { Host, Join, Single };

    void setupUI();
    void buttonPressed(Button button);

    virtual void handleEvent(const sf::Event& event);
    virtual void update(float delta);
    virtual void draw();

private:
    tgui::Gui gui;
    tgui::Button::Ptr hostButton;
    tgui::Button::Ptr joinButton;
    tgui::Button::Ptr spButton;
    tgui::EditBox::Ptr ipAddrInput;
};
