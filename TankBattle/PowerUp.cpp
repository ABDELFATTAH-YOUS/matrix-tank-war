#include "PowerUp.h"

PowerUp::PowerUp() {
    x = y = 0;
    width = height = 2;
    type = 0;
    active = false;
    spawnTime = 0;
}

// Place the box. Does nothing if one is already on screen.
void PowerUp::spawn(int startX, int startY, int w, int h, int pType) {
    if (active) return;

    x = startX;
    y = startY;
    width = w;
    height = h;
    type = pType;
    active = true;
}

// Redraw every frame so bullets passing nearby do not erase it
void PowerUp::update(DisplayManager &display, InputManager &input) {
    if (!active) return;
    draw(display);
}

void PowerUp::draw(DisplayManager &display) {
    display.drawRect(x, y, width, height, true);
}

void PowerUp::destroy(DisplayManager &display) {
    display.drawRect(x, y, width, height, false);
}

bool PowerUp::isActive() { return active; }
void PowerUp::deactivate() { active = false; }
int PowerUp::getType() { return type; }
int PowerUp::getX() { return x; }
int PowerUp::getY() { return y; }
int PowerUp::getWidth() { return width; }
int PowerUp::getHeight() { return height; }
