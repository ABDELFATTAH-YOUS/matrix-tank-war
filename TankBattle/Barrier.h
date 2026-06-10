/*
 * Barrier.h - a wall that slides across the screen and blocks bullets
 */
#pragma once
#include <Arduino.h>
#include "Display.h"
#include "Config.h"
#include "InputManager.h"

class Barrier {
private:
    int x, y;
    int width, height;
    int dir;                    // +1 = moves right, -1 = moves left
    bool active;
    unsigned long lastMoveTime;


public:
int DEFAULT_Barrier_SPEED ;     // ms between steps (default 150)
    Barrier();

    void spawn(int startX, int startY, int w, int h, int direction);  // appear on screen
    void update(DisplayManager &display, InputManager &input);        // move if it is time

    void draw(DisplayManager &display);
    void destroy(DisplayManager &display);

    bool isActive();
    void deactivate();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
};
