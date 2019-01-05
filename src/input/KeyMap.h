#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class KeyMap {
public:
    KeyMap();
    KeyMap(std::string bindingsPath);

    enum ID { FORWARD = 0, BACKWARD, TURNLEFT, TURNRIGHT };

    void loadBindingsFromFile();  // std::string path);
    void generateDefaultConfigFile();
    bool isKeyPressed(KeyMap::ID id);

    std::map<KeyMap::ID, sf::Keyboard::Key> keys;

private:
    bool hasConfigFile();

    std::string defaultConfig = "";
};
