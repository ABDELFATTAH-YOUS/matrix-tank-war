#include "Barrier.h"

Barrier::Barrier() {
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    dir = 0;
    active = false;
    lastMoveTime = 0;
    DEFAULT_Barrier_SPEED=150;
}

// Place the barrier. Does nothing if it is already on screen.
void Barrier::spawn(int startX, int startY, int w, int h, int direction) {
    if (active) return;

    x = startX;
    y = startY;
    width = w;
    height = h;
    dir = direction;
    active = true;
}

// Move one pixel sideways; turn off when it leaves the screen
void Barrier::update(DisplayManager &display, InputManager &input) {
    if (!active) return;

    if (input.isTimePassed(lastMoveTime, DEFAULT_Barrier_SPEED)) {

        destroy(display);

        x += dir;

        if (x >= SCREEN_WIDTH || x + width < 0) {
            active = false;
        } else {
            draw(display);
        }
    }
}

void Barrier::draw(DisplayManager &display) {

    display.drawRect(x, y, width, height, true);
}

void Barrier::destroy(DisplayManager &display) {
    display.drawRect(x, y, width, height, false);
}

bool Barrier::isActive() { return active; }
void Barrier::deactivate() { active = false; }
int Barrier::getX() { return x; }
int Barrier::getY() { return y; }
int Barrier::getWidth() { return width; }
int Barrier::getHeight() { return height; }
