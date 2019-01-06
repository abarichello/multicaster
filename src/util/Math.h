#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>

namespace Math {
    // Rotation matrix from https://en.wikipedia.org/wiki/Rotation_matrix
    sf::Vector2f rotateVector(sf::Vector2f input, float value) {
        float x = (input.x * std::cos(value) - input.y * std::sin(value));
        float y = (input.x * std::sin(value) + input.y * std::cos(value));
        return sf::Vector2f(x, y);
    }
};  // namespace Math
