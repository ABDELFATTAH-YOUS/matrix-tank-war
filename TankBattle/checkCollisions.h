/*
 * checkCollisions.h - hit tests between a bullet and other objects
 *
 * A bullet is one pixel, so every test is "is this point inside
 * the object's rectangle?".
 */
#pragma once
#include "Tank.h"
#include "Bullet.h"
#include "Barrier.h"
#include "PowerUp.h"

class CollisionManager {
private:
    bool isPointInRect(int bx, int by, int rx, int ry, int rw, int rh);

public:
    bool checkBulletTank(Bullet &bullet, Tank &tank, bool isTankStarted);  // only if the tank is in play
    bool checkBulletBarrier(Bullet &bullet, Barrier &barrier);
    bool checkBulletPowerUp(Bullet &bullet, PowerUp &powerUp);
};
