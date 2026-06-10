/*
 * Tank.h - a player's tank: a 3x3 block with a 1-pixel cannon
 *
 * Note: isPlayer1 == true means the TOP tank (cannon points down).
 */
#pragma once
#include <Arduino.h>
#include "Display.h"
#include "Config.h"
#include "InputManager.h"
#include "SoundManager.h"


class Tank {
private:
    int x, y;                  // top-left corner
    int width, height;
    bool isPlayer1;            // true = top tank, false = bottom tank
    unsigned long lastMoveTime;
    SoundManager sndm;

public:
    Tank(int startX, int startY, int w, int h, bool player1);
    void draw(DisplayManager &display);      // draw body + cannon
    void destroy(DisplayManager &display);   // erase body + cannon
    bool handleMovement(InputManager &input, DisplayManager &display, uint8_t btnLeft, uint8_t btnRight);
    void moveLeft();
    void moveRight();
    int getX();
    int getY();
    bool tankmoved();          // declared but not implemented
    int getWidth();
    int getHeight();
    int getCannonX();          // where a new bullet starts
    int getCannonY();
};
