#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Debug.h"

class FPS : public Debug {
public:
    FPS();

    void update(float delta);

private:
    int frameCount = 0;
    int updateRate = 2;
    float delta = 0.0f;
    float fps = 0.0f;
};
