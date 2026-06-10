/*
 * TextManager.h - scrolls text up the LED screen
 *
 * Letters are stacked vertically (one 5x7 letter every 8 rows)
 * and move up one pixel at a time.
 */
#ifndef TEXT_MANAGER_H
#define TEXT_MANAGER_H

#include <Arduino.h>
#include "Display.h"
#include "InputManager.h"

class TextManager {
private:
    String currentText;
    int yPos;                     // y of the first letter (starts below the screen)
    unsigned long lastScrollTime;
    bool active;
    int scrollSpeed;              // ms per 1-pixel step

    void drawChar(DisplayManager &display, int x, int y, char c);

public:
    TextManager();
    void startScroll(String text, int speed = 50);                // start a new text
    bool update(DisplayManager &display, InputManager &input);    // false when finished
    bool isActive();
};

#endif
