/*
 * SoundManager.h - buzzer sound effects made with tone()
 *
 * Note: most effects use delay(), so the game pauses while they play.
 */
#pragma once
#include <Arduino.h>
#include "Config.h"

class SoundManager {

public:

    // Building blocks
    void tonefade(int pin, int freq, int dur);                     // one tone, then wait (not used yet)
    void sweep(int pin, int from, int to, int step, int stepDelay); // slide from one pitch to another
    void blip(int freq, int dur, int silenceAfter);                // short beep (not used yet)

    // Game sounds
    void tankMoveRightSound();   // tank moves (left or right)
    void explosionSound();       // not used yet
    void gunShotSound();         // bullet fired
    void wallHitSound();         // bullet hits a barrier
    void targetHitSound();       // not used yet
    void successSound();         // good power-up / match win
    void errorSound();           // not used yet
    void sadSound();             // bad power-up
    void gameStartSound();       // new round
    void gameOverSound();        // a tank was hit

    void backgroundMelody();     // declared but not implemented

};
