#include "Game.h"

// Player 1 starts at the bottom (y = 29), player 2 at the top (y = 0)
Game::Game() : tank1(0, 29, 3, 3, false), tank2(0, 0, 3, 3, true) {
    started1 = false;
    started2 = false;
    lastTimebullet1 = 0;
    lastTimebullet2 = 0;
    poweruplastTime = 0;

    p1Score = 0;
    p2Score = 0;

    p1FireRate = 150;
    p2FireRate = 150;
    p1FreezeTime = 0;
    p2FreezeTime = 0;

    lcdMessage = "";
    lcdMessageTime = 0;

    currentState = STATE_START_SCREEN;
    textMng.startScroll("START", 60);
}

// Start a new round: clear the screen, place tanks at random x,
// remove all bullets, barriers and power-ups, reset fire rates.
// Scores are kept.
void Game::reset(DisplayManager &display) {
    display.clearAll();

    sndm.gameStartSound();

    int randx1 = random(0, 14);
    int randx2 = random(0, 14);

    tank1 = Tank(randx1, 29, 3, 3, false);
    tank2 = Tank(randx2, 0, 3, 3, true);

    for(int i=0; i<10; i++){
       bullet1[i].deactivate();
       bullet2[i].deactivate();
    }

    barrier1.deactivate();
    barrier2.deactivate();
    powerup.deactivate();

    started1 = started2 = false;

    p1FireRate = 150;
    p2FireRate = 150;
    p1FreezeTime = 0;
    p2FreezeTime = 0;
}

int Game::getP1Score() { return p1Score; }
int Game::getP2Score() { return p2Score; }

// Main state machine: start screen -> playing -> game over -> start screen
void Game::update(DisplayManager &display, InputManager &input) {
    if (currentState == STATE_START_SCREEN) {
        // When the start text has finished scrolling, begin a round
        if (!textMng.update(display, input)) {
            reset(display);
            currentState = STATE_PLAYING;
        }
    }
    else if (currentState == STATE_PLAYING) {
        handleTanks(display, input);
        handleBarriers(display, input);
        handlePowerUp(display, input);
    }
    else if (currentState == STATE_GAMEOVER_SCREEN) {
        // When the winner text has finished scrolling, go back to start
        if (!textMng.update(display, input)) {
            currentState = STATE_START_SCREEN;
            textMng.startScroll("START", 60);
        }
    }
}

// Tank movement, shooting, bullet movement and tank hits
void Game::handleTanks(DisplayManager &display, InputManager &input) {
    // A frozen player cannot move or shoot
    bool p1CanMove = (millis() > p1FreezeTime);
    bool p2CanMove = (millis() > p2FreezeTime);

    // A tank appears on the screen after its first move
    if (p1CanMove && tank1.handleMovement(input, display, BTNLEFT1, BTNRIGHT1) && !started1){tank1.draw(display); started1=true;}
    if (p2CanMove && tank2.handleMovement(input, display, BTNLEFT2, BTNRIGHT2) && !started2){tank2.draw(display); started2=true;}

    // Player 1 shoots: use the first free bullet (fire rate limited)
    if (p1CanMove && input.isPressed(BTNFIRE1) && started1) {
        if (input.isTimePassed(lastTimebullet1, p1FireRate)) {
            for(int i=0; i<10; i++) {
                if (!bullet1[i].isActive()) {
                    bullet1[i].fire(tank1.getCannonX(), tank1.getCannonY(), true);
                    lastTimebullet1 = millis();
                    break;
                }
            }
        }
    }

    // Player 2 shoots
    if (p2CanMove && input.isPressed(BTNFIRE2) && started2) {
        if (input.isTimePassed(lastTimebullet2, p2FireRate)) {
            for(int i=0; i<10; i++) {
                if (!bullet2[i].isActive()) {
                    bullet2[i].fire(tank2.getCannonX(), tank2.getCannonY(), false);
                    lastTimebullet2 = millis();
                    break;
                }
            }
        }
    }

    // Move all bullets
    for(int i=0; i<10; i++) bullet1[i].update(display, input);
    for(int i=0; i<10; i++) bullet2[i].update(display, input);

    // Player 1 bullet hits player 2 tank
    for(int i=0; i<10; i++) {
        if (chk.checkBulletTank(bullet1[i], tank2, started2)) {
            bullet1[i].destroy(display);
            bullet1[i].deactivate();

            showExplosion(display, tank2);
            p1Score++;

            if (p1Score >= 5) {
                // Player 1 wins the match
                sndm.successSound();
                p1Score = 0;
                p2Score = 0;
                currentState = STATE_GAMEOVER_SCREEN;
                textMng.startScroll("P1 WINS", 70);
            } else {
                // Next round
                sndm.gameOverSound();
                delay(1000);
                reset(display);
            }
            break;
        }
    }

    // Player 2 bullet hits player 1 tank
    for(int i=0; i<10; i++) {
        if (chk.checkBulletTank(bullet2[i], tank1, started1)) {
            bullet2[i].destroy(display);
            bullet2[i].deactivate();

            showExplosion(display, tank1);
            p2Score++;

            if (p2Score >= 5) {
                // Player 2 wins the match
                sndm.successSound();
                p1Score = 0;
                p2Score = 0;
                currentState = STATE_GAMEOVER_SCREEN;
                textMng.startScroll("P2 WINS", 70);
            } else {
                // Next round
                sndm.gameOverSound();
                delay(1000);
                reset(display);
            }
            break;
        }
    }
}

// Spawn moving barriers at random and let them block bullets
void Game::handleBarriers(DisplayManager &display, InputManager &input) {
    // About 1% chance per loop to spawn barrier 1 (only when both tanks are in play)
    if (started1 && started2 && !barrier1.isActive()) {
        if (random(0, 200) < 2) {
            int startY = random(10, 20);                  // middle of the screen
            int dir = (random(0, 2) == 0) ? 1 : -1;       // move right or left
            int startX = (dir == 1) ? random(0, 7) : (SCREEN_WIDTH - random(2, 10));
            barrier1.spawn(startX, startY, 3, 1, dir);
        }
    }

    // Barrier 2 is faster (moves every 100 ms)
    if (started1 && started2 && !barrier2.isActive()) {
        if (random(0, 200) < 2) {
            int startY = random(10, 20);
            int dir = (random(0, 2) == 0) ? 1 : -1;
            int startX = (dir == 1) ? random(0, 7) : (SCREEN_WIDTH - random(2, 10));
            barrier2.DEFAULT_Barrier_SPEED = 100;
            barrier2.spawn(startX, startY, 3, 1, dir);
        }
    }

    barrier1.update(display, input);
    barrier2.update(display, input);

    // Remove any bullet that hits a barrier
    for(int i=0; i<10; i++) {
        if (chk.checkBulletBarrier(bullet1[i], barrier1) || chk.checkBulletBarrier(bullet1[i], barrier2)) {
            bullet1[i].destroy(display);
            bullet1[i].deactivate();
            sndm.wallHitSound();
        }
    }

    for(int i=0; i<10; i++) {
        if (chk.checkBulletBarrier(bullet2[i], barrier1) || chk.checkBulletBarrier(bullet2[i], barrier2)) {
            bullet2[i].destroy(display);
            bullet2[i].deactivate();
            sndm.wallHitSound();
        }
    }
}

// Blink the hit tank a few times (note: this blocks for 500 ms)
void Game::showExplosion(DisplayManager &display, Tank &tk) {
    tk.destroy(display);
    delay(100);
    tk.draw(display);
    delay(100);
    tk.destroy(display);
    delay(100);
    tk.draw(display);
    delay(100);
    tk.destroy(display);
    delay(100);
}

// Spawn a mystery box every 5 seconds; shooting it gives a random effect
void Game::handlePowerUp(DisplayManager &display, InputManager &input) {
    if (started1 && started2 && !powerup.isActive()) {
        if (input.isTimePassed(poweruplastTime, 5000)) {
            int startY = random(10, 20);
            int type = (random(0, 2) == 0) ? 1 : 0;   // 1 = good, 0 = bad
            int startX =  random(0, SCREEN_WIDTH-3);

            // Good box is 2x2, bad box is 3x2
            if (type) {
                powerup.spawn(startX, startY, 2, 2, type);
            } else {
                powerup.spawn(startX, startY, 3, 2, type);
            }
            poweruplastTime = millis();
        }
    }

    powerup.update(display, input);

    // Player 1 hits the box
    for(int i=0; i<10; i++) {
        if (chk.checkBulletPowerUp(bullet1[i], powerup)) {
            bullet1[i].destroy(display);
            bullet1[i].deactivate();

            if (powerup.getType() == 1) {
                sndm.successSound();
                applyGoodEffect(1);
            } else {
                sndm.sadSound();
                applyBadEffect(1);
            }
            powerup.destroy(display);
            powerup.deactivate();
        }
    }

    // Player 2 hits the box
    for(int i=0; i<10; i++) {
        if (chk.checkBulletPowerUp(bullet2[i], powerup)) {
            bullet2[i].destroy(display);
            bullet2[i].deactivate();

            if (powerup.getType() == 1) {
                sndm.successSound();
                applyGoodEffect(2);
            } else {
                sndm.sadSound();
                applyBadEffect(2);
            }
            powerup.destroy(display);
            powerup.deactivate();
        }
    }
}

// ==========================================================
// POWER-UP EFFECTS (message is kept for 3 seconds)
// ==========================================================

// Random reward: +1 point, fast fire, or freeze the opponent for 3 s
void Game::applyGoodEffect(int playerNum) {
    int effect = random(0, 3);
    if (playerNum == 1) {
        if (effect == 0)      { p1Score++; lcdMessage = "P1 +1 POINT     "; }
        else if (effect == 1) { p1FireRate = 50; lcdMessage = "P1 FAST FIRE    "; }
        else if (effect == 2) { p2FreezeTime = millis() + 3000; lcdMessage = "P2 FROZEN       "; }
    } else {
        if (effect == 0)      { p2Score++; lcdMessage = "P2 +1 POINT     "; }
        else if (effect == 1) { p2FireRate = 50; lcdMessage = "P2 FAST FIRE    "; }
        else if (effect == 2) { p1FreezeTime = millis() + 3000; lcdMessage = "P1 FROZEN       "; }
    }
    lcdMessageTime = millis();
}

// Random penalty: -1 point, slow fire, or freeze yourself for 3 s
void Game::applyBadEffect(int playerNum) {
    int effect = random(0, 3);
    if (playerNum == 1) {
        if (effect == 0)      { p1Score--; if(p1Score < 0) p1Score = 0; lcdMessage = "P1 -1 POINT     "; }
        else if (effect == 1) { p1FireRate = 400; lcdMessage = "P1 SLOW FIRE    "; }
        else if (effect == 2) { p1FreezeTime = millis() + 3000; lcdMessage = "P1 FROZEN       "; }
    } else {
        if (effect == 0)      { p2Score--; if(p2Score < 0) p2Score = 0; lcdMessage = "P2 -1 POINT     "; }
        else if (effect == 1) { p2FireRate = 400; lcdMessage = "P2 SLOW FIRE    "; }
        else if (effect == 2) { p2FreezeTime = millis() + 3000; lcdMessage = "P2 FROZEN       "; }
    }
    lcdMessageTime = millis();
}

// Returns the last event message, or "" if it is older than 3 seconds
String Game::getLcdMessage() {
    if (millis() - lcdMessageTime > 3000) {
        return "";
    }
    return lcdMessage;
}
