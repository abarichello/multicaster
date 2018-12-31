#pragma once

#include <SFML/Graphics.hpp>

#include "Debug.h"

#include <string>

class FPS : public Debug {
public:
    FPS();

    void process(float delta);

private:
    int frameCount = 0;
    int updateRate = 2;
    float delta = 0.0f;
    float fps = 0.0f;
};
