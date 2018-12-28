#pragma once

#include "../ResourceHolder.h"
#include "State.h"

class MainMenuIntro : public State {
public:
private:
    FontHolder fonts;
    sf::Text menuText;
};
