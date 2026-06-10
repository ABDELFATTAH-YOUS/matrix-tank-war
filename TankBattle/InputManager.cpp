#include "InputManager.h"

// Buttons are active-HIGH with external pull-down resistors
void InputManager::begin() {

    pinMode(BTNLEFT1,INPUT);
    pinMode(BTNRIGHT1,INPUT);
    pinMode(BTNFIRE1,INPUT);

    pinMode(BTNLEFT2,INPUT);
    pinMode(BTNRIGHT2,INPUT);
    pinMode(BTNFIRE2,INPUT);
}

// Returns true once every `interval` ms and saves the time in lastTime.
// Used everywhere instead of delay(), so the game keeps running.
bool InputManager::isTimePassed(unsigned long &lastTime, unsigned long interval) {

    unsigned long currentTime = millis();

    if (currentTime - lastTime >= interval) {
        lastTime = currentTime;
        return true;
    }

    return false;
}

// True if the button is held down.
// Each pin can report a press at most once every 50 ms.
bool InputManager::isPressed(uint8_t pin) {

    // Last press time for each pin number
    static unsigned long lastPressTime[256] = {0};

    if (digitalRead(pin) == HIGH) {

        if (isTimePassed(lastPressTime[pin], 50)) {
            return true;
        }
    }

    return false;
}
