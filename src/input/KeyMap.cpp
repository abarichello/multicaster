#include <cassert>

#include "KeyMap.h"

// Class used to load keybinds from a config file
KeyMap::KeyMap() {
    loadBindingsFromFile();
}

KeyMap::KeyMap(std::string bindingsPath) {
    // loadBindingsFromFile(bindingsPath);
}

// Load the keys.cfg file that's placed with the executable into the keymap
void KeyMap::loadBindingsFromFile() {  // std::string path) {
    // TODO: actualy load settings from file
    keys[KeyMap::FORWARD] = sf::Keyboard::W;
    keys[KeyMap::BACKWARD] = sf::Keyboard::S;
    keys[KeyMap::TURNLEFT] = sf::Keyboard::A;
    keys[KeyMap::TURNRIGHT] = sf::Keyboard::D;
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
}
