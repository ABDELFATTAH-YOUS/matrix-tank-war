/*
 * PowerUp.h - a mystery box. Shoot it to get a random effect.
 *
 * type 1 = good (2x2 box), type 0 = bad (3x2 box)
 */
#pragma once
#include "Display.h"
#include "InputManager.h"
#include "Config.h"

class PowerUp {

private:
    int x, y;
    int width, height;
    int type;                   // 1 = good, 0 = bad
    bool active;
    unsigned long spawnTime;    // not used yet

public:
    PowerUp();
    void spawn(int startX, int startY, int w, int h, int pType);
    void update(DisplayManager &display, InputManager &input);  // keep it drawn
    void draw(DisplayManager &display);
    void destroy(DisplayManager &display);
    bool isActive();
    void deactivate();
    int getType();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
};
