/*
 * InputManager.h - button reading and a small timer helper
 */
#pragma once
#include <Arduino.h>
#include "Config.h"

class InputManager {
public:
    void begin();                                                  // set button pins as inputs
    bool isPressed(uint8_t pin);                                   // is this button pressed?
    bool isTimePassed(unsigned long &lastTime, unsigned long interval); // non-blocking timer
};
