#include "SoundManager.h"

// ---------- Building blocks ----------

void SoundManager::tonefade(int pin, int freq, int dur) {
  tone(pin, freq, dur);
  delay(dur + 2);
}

// Change the pitch step by step from `from` to `to`
void SoundManager::sweep(int pin, int from, int to, int step, int stepDelay) {
  if (from > to) {
    for (int f = from; f > to; f -= abs(step)) {
      tone(pin, f);
      delay(stepDelay);
    }
  } else {
    for (int f = from; f < to; f += abs(step)) {
      tone(pin, f);
      delay(stepDelay);
    }
  }
  noTone(pin);
}

void SoundManager::blip(int freq, int dur, int silenceAfter) {
  tone(buzzer, freq, dur);
  delay(dur + silenceAfter);
}

// ---------- Game sounds ----------

// Short click when a tank moves
void SoundManager::tankMoveRightSound() {
  tone(buzzer, 1000, 80);
  delay(25);
  noTone(buzzer);
}

// High crack, falling sweep, random rumble, low tail
void SoundManager::explosionSound() {
  tone(buzzer, 4000); delay(4);
  tone(buzzer, 3000); delay(4);
  tone(buzzer, 2000); delay(6);

  sweep(buzzer, 1800, 60, 20, 3);

  for (int i = 0; i < 10; i++) {
    tone(buzzer, 50 + random(60));
    delay(20 + random(15));
  }

  sweep(buzzer, 120, 50, 8, 12);
  noTone(buzzer);
}

// Fast drop from high to low pitch (~110 ms)
void SoundManager::gunShotSound() {

  // sharp start
  tone(buzzer, 4500); delay(3);
  tone(buzzer, 3500); delay(3);
  tone(buzzer, 2500); delay(4);

  // body
  tone(buzzer, 1500); delay(8);
  tone(buzzer, 1000); delay(10);

  // tail
  tone(buzzer, 700);  delay(18);
  tone(buzzer, 500);  delay(20);
  tone(buzzer, 350);  delay(25);
  tone(buzzer, 200);  delay(20);
  noTone(buzzer);
}

// Metallic "ping" when a bullet hits a barrier
void SoundManager::wallHitSound() {

  // impact
  tone(buzzer, 2500); delay(4);
  tone(buzzer, 1800); delay(5);
  tone(buzzer, 1200); delay(6);

  // ricochet
  sweep(buzzer, 500, 1600, 45, 3);

  tone(buzzer, 900); delay(10);
  tone(buzzer, 600); delay(12);
  noTone(buzzer);
}

void SoundManager::targetHitSound() {

  tone(buzzer, 1200); delay(10);
  tone(buzzer, 800);  delay(12);

  tone(buzzer, 700);  delay(15);
  tone(buzzer, 900);  delay(18);
  tone(buzzer, 1100); delay(18);
  tone(buzzer, 1400); delay(20);
  tone(buzzer, 1700); delay(70);
  noTone(buzzer);
}

// Rising happy melody (C - E - G - G - high C)
void SoundManager::successSound() {
  int notes[] = {523, 659, 784, 784, 1047};
  int durs[]  = { 70,  70,  70,  40,  220};
  int gaps[]  = { 15,  15,  10,  10,   0};
  for (int i = 0; i < 5; i++) {
    tone(buzzer, notes[i]);
    delay(durs[i]);
    noTone(buzzer);
    delay(gaps[i]);
  }
}

void SoundManager::errorSound() {
  sweep(buzzer, 600, 350, 15, 8);
  delay(20);
  sweep(buzzer, 380, 180, 12, 10);
  noTone(buzzer);
}

// Slow falling melody
void SoundManager::sadSound() {
  int notes[] = {622, 587, 554, 494, 440, 415, 370};
  int durs[]  = {130, 130, 130, 160, 160, 180, 500};
  for (int i = 0; i < 7; i++) {
    tone(buzzer, notes[i]);
    delay(durs[i]);
    noTone(buzzer);
    delay(15);
  }
}

// Short fanfare at the start of each round
void SoundManager::gameStartSound() {
  int notes[] = {392, 523, 523, 659, 784, 659, 784, 1047};
  int durs[]  = { 60,  60,  60,  80, 100,  60, 100,  300};
  int gaps[]  = { 10,  10,  10,  10,  15,  10,  15,   0};
  for (int i = 0; i < 8; i++) {
    tone(buzzer, notes[i]);
    delay(durs[i]);
    noTone(buzzer);
    delay(gaps[i]);
  }
}

// Long falling melody when a tank is hit
void SoundManager::gameOverSound() {
  int notes[] = {740, 698, 659, 622, 587, 554, 523, 494, 440, 370};
  int durs[]  = {100, 100, 100, 100, 100, 100, 120, 140, 180, 600};
  for (int i = 0; i < 10; i++) {
    tone(buzzer, notes[i]);
    delay(durs[i]);
    noTone(buzzer);
    delay(8);
  }
}
