#include <cassert>

#include "KeyMap.h"

// Class used to load keybinds from a config file
KeyMap::KeyMap() {
    loadBindingsFromFile();
}

// Load the keys.cfg file that's placed with the executable into the keymap
void KeyMap::loadBindingsFromFile() {
    // TODO: actualy load settings from file
    keys.clear();
    keys[KeyMap::FORWARD] = sf::Keyboard::W;
    keys[KeyMap::BACKWARD] = sf::Keyboard::S;
    keys[KeyMap::LEFT] = sf::Keyboard::A;
    keys[KeyMap::RIGHT] = sf::Keyboard::D;
    keys[KeyMap::TURNLEFT] = sf::Keyboard::Left;
    keys[KeyMap::TURNRIGHT] = sf::Keyboard::Right;
}

// Check for an existing config file, if it doe not exist generate a default one
void KeyMap::generateDefaultConfigFile() {
}

bool KeyMap::isKeyPressed(KeyMap::ID id) {
    auto found = keys.find(id);
    assert(found != keys.end());
    return sf::Keyboard::isKeyPressed(found->second);
}

// Checks if the current directory already has a config file
bool KeyMap::hasConfigFile() {
    return true;
}
