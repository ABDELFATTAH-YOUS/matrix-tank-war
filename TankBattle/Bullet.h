/*
 * Bullet.h - a single pixel that flies up or down the screen
 */
#pragma once
#include <Arduino.h>
#include "Display.h"
#include "Config.h"
#include "Config.h"
#include "InputManager.h"
#include "SoundManager.h"

class Bullet {
private:
    int x, y;
    bool active;        // is the bullet on the screen?
    bool isPlayer1;     // true = flies up (player 1), false = flies down (player 2)
    unsigned long lastMoveTime;
    SoundManager sndm;

public:
    Bullet();

    void fire(int startX, int startY, bool player1);            // start flying
    void update(DisplayManager &display, InputManager &input);  // move one step if it is time

    void draw(DisplayManager &display);
    void destroy(DisplayManager &display);   // erase from the screen

    bool isActive();
    int getX();
    int getY();
    void deactivate();
};
