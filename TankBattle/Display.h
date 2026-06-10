/*
 * Display.h - simple drawing on the 16 x 32 LED screen
 *
 * Hides the 8 separate modules: callers just use screen (x, y).
 */
#pragma once
#include <Arduino.h>
#include <LedControl.h>
#include "Config.h"
#include "Matrix.h"

class DisplayManager {
private:
    // Driver for the chain of MAX7219 modules
    LedControl lc = LedControl(DIN, CLK, CS, MATRIX_COUNT);

public:
    void begin();                                        // wake up and clear all modules
    void setPixel(int x, int y, bool state);             // turn one pixel on/off
    void clearAll();                                     // turn every pixel off
    void clearRegion(int x1, int y1, int x2, int y2);    // turn off a box (not used yet)
    void drawRect(int x, int y, int w, int h, bool state); // fill a w x h box
};
