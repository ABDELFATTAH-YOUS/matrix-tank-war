/*
 * Game.h - the game itself: rules, scoring and screen states
 *
 * Owns all game objects (tanks, bullets, barriers, power-up)
 * and is updated once per loop() by the main sketch.
 */
#ifndef GAME_H
#define GAME_H

#include "Display.h"
#include "InputManager.h"
#include "Tank.h"
#include "Bullet.h"
#include "Barrier.h"
#include "PowerUp.h"
#include "checkCollisions.h"
#include "TextManager.h"

#include "SoundManager.h"

// The three screens of the game
enum GameState {
    STATE_START_SCREEN,     // scrolling start text
    STATE_PLAYING,          // the match
    STATE_GAMEOVER_SCREEN   // scrolling winner text
};

class Game {
private:
    Tank tank1;             // player 1 (bottom)
    Tank tank2;             // player 2 (top)
    Bullet bullet1[10];     // player 1 bullets
    Bullet bullet2[10];     // player 2 bullets
    Barrier barrier1;
    Barrier barrier2;
    PowerUp powerup;
    CollisionManager chk;
    TextManager textMng;

    bool started1, started2;                     // has the player moved yet this round?
    unsigned long lastTimebullet1, lastTimebullet2; // last shot time
    unsigned long poweruplastTime;               // last power-up spawn time

    int p1Score, p2Score;
    int p1FireRate, p2FireRate;                  // min time between shots (ms)
    unsigned long p1FreezeTime, p2FreezeTime;    // player is frozen until this time
    SoundManager sndm;
    GameState currentState;

    String lcdMessage;                           // last event message (not shown yet)
    unsigned long lcdMessageTime;


    void applyGoodEffect(int playerNum);   // reward from a power-up
    void applyBadEffect(int playerNum);    // penalty from a power-up
    void handleTanks(DisplayManager &display, InputManager &input);
    void handleBarriers(DisplayManager &display, InputManager &input);
    void handlePowerUp(DisplayManager &display, InputManager &input);
    void showExplosion(DisplayManager &display, Tank &tk);

public:
    Game();
    void reset(DisplayManager &display);                      // start a new round
    void update(DisplayManager &display, InputManager &input); // call every loop()

    int getP1Score();
    int getP2Score();

    String getLcdMessage();   // event message, empty after 3 seconds
};

#endif
