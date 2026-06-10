#include "Tank.h"

Tank::Tank(int startX, int startY, int w, int h, bool player1) {
   x = startX;
   y = startY;
   width = w;
   height = h;
   isPlayer1 = player1;
   lastMoveTime=0;
}

// Draw the body and the cannon pixel in front of it
void Tank::draw(DisplayManager &display) {

    display.drawRect(x, y, width, height, true);

    if (!isPlayer1) {
        display.setPixel(x + 1, y - 1 , true);          // bottom tank: cannon above
    } else {

        display.setPixel(x + 1,y + height , true);      // top tank: cannon below
    }
}

// Erase the body and the cannon
void Tank::destroy(DisplayManager &display) {

    display.drawRect(x, y, width, height, false);

    if (!isPlayer1) {
        display.setPixel(x + 1, y - 1, false);
    } else {
        display.setPixel(x + 1, y + height, false);
    }
}

// Move one pixel left (stops at the screen edge)
void Tank::moveLeft() {
    if (x > 0) x -= 1;
    sndm.tankMoveRightSound();
}

// Move one pixel right (stops at the screen edge)
void Tank::moveRight() {

    if (x + width < SCREEN_WIDTH) x += 1;
    sndm.tankMoveRightSound();
}

// Read the buttons and move at most once every DEFAULT_TANK_SPEED ms.
// Returns true if the tank moved.
bool Tank::handleMovement(InputManager &input, DisplayManager &display, uint8_t btnLeft, uint8_t btnRight) {

    bool moved = false;

    if (input.isTimePassed(lastMoveTime, DEFAULT_TANK_SPEED)) {

        if (input.isPressed(btnLeft)) {
            destroy(display);   // erase at old position
            moveLeft();
            moved = true;
        }

        else if (input.isPressed(btnRight)) {
            destroy(display);
            moveRight();
            moved = true;
        }

        if (moved) {
            draw(display);      // draw at new position
        }
    }

    return moved;
}


// Bullets start in the middle column, just in front of the cannon
int Tank::getCannonX() {
    return x + 1;
}

int Tank::getCannonY() {

    if (!isPlayer1) {
        return y - 2;
    } else {
        return y + height+1;
    }
}
int Tank::getHeight() { return height; }
int Tank::getX() { return x; }
int Tank::getY() { return y; }
int Tank::getWidth() { return width; }
