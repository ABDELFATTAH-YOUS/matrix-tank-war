#include "checkCollisions.h"

// True if point (bx, by) is inside the rectangle (rx, ry, rw, rh)
bool CollisionManager::isPointInRect(int bx, int by, int rx, int ry, int rw, int rh) {
    return (bx >= rx && bx < rx + rw && by >= ry && by < ry + rh);
}


bool CollisionManager::checkBulletPowerUp(Bullet &bullet, PowerUp &powerUp){

    if (!bullet.isActive() || !powerUp.isActive()) {
        return false;
    }

    int bx = bullet.getX();
    int by = bullet.getY();

    int rx = powerUp.getX();
    int ry = powerUp.getY();
    int rw = powerUp.getWidth();
    int rh = powerUp.getHeight();

    return isPointInRect(bx, by, rx, ry, rw, rh);
}


// A tank that has not moved yet this round cannot be hit
bool CollisionManager::checkBulletTank(Bullet &bullet, Tank &tank, bool isTankStarted) {

    if (!bullet.isActive() || !isTankStarted) {
        return false;
    }

    int bx = bullet.getX();
    int by = bullet.getY();

    int rx = tank.getX();
    int ry = tank.getY();
    int rw = tank.getWidth();
    int rh = tank.getHeight();

    return isPointInRect(bx, by, rx, ry, rw, rh);
}


bool CollisionManager::checkBulletBarrier(Bullet &bullet, Barrier &barrier) {

    if (!bullet.isActive() || !barrier.isActive() ) {
        return false;
    }

    int bx = bullet.getX();
    int by = bullet.getY();

    int rx = barrier.getX();
    int ry = barrier.getY();
    int rw = barrier.getWidth();
    int rh = barrier.getHeight();

    return isPointInRect(bx, by, rx, ry, rw, rh);
}
