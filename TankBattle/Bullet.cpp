#include "Bullet.h"

Bullet::Bullet() {
    x = 0;
    y = 0;
    active = false;
    isPlayer1 = false;
    lastMoveTime = 0;

}

// Start the bullet at (startX, startY). Does nothing if it is already flying.
void Bullet::fire(int startX, int startY, bool player) {
    if(active) return;

    x = startX;
    y = startY;
    active = true;
    isPlayer1 = player;
    sndm.gunShotSound();
}

// Move one pixel every DEFAULT_BULLET_SPEED ms.
// The bullet turns off when it leaves the screen.
void Bullet::update(DisplayManager &display, InputManager &input) {
    if (!active) return;

    if (input.isTimePassed(lastMoveTime, DEFAULT_BULLET_SPEED)) {

        destroy(display);

        if (isPlayer1) {
            // Player 1 bullet goes up
            if (y > 0) {
                y -= 1;

            } else {
                active = false;
            }
        } else {
            // Player 2 bullet goes down
            if (y < SCREEN_HEIGHT - 1) {
                y += 1;

            } else {
                active = false;
            }
        }

        if (active) {
            draw(display);
        }
    }
}

void Bullet::draw(DisplayManager &display) {
    display.setPixel(x, y, true);
}

void Bullet::destroy(DisplayManager &display) {
    display.setPixel(x, y, false);
}

bool Bullet::isActive() { return active; }
int Bullet::getX() { return x; }
int Bullet::getY() { return y; }
void Bullet::deactivate() { active = false; }
