#include "FPS.h"

FPS::FPS() : Debug() {
}

void FPS::process(float delta) {
    frameCount++;
    this->delta += delta;
    if (this->delta > 1.0 / updateRate) {
        fps = frameCount / this->delta;
        frameCount = 0;
        this->delta -= 1.0 / updateRate;
    }
    std::string text = "FPS: " + std::to_string(fps);
    this->setText(text);
}
