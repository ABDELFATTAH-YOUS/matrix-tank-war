/*
 * Config.h - all constants and pin numbers in one place
 */
#pragma once

// Screen: 8 MAX7219 modules (2 wide x 4 tall) = 16 x 32 pixels
#define MATRIX_COUNT 8
#define SCREEN_WIDTH 16
#define SCREEN_HEIGHT 32

// MAX7219 pins
#define CLK 12
#define CS 10
#define DIN 11
#define LIGHT 8     // LED brightness (0-15)
#define buzzer 8    // buzzer pin

// Player 1 buttons (bottom tank)
#define BTNLEFT1 A0
#define BTNRIGHT1 A2
#define BTNFIRE1 A1

// Player 2 buttons (top tank)
#define BTNLEFT2 A5
#define BTNRIGHT2 A3
#define BTNFIRE2 A4

// Time between steps in milliseconds (smaller = faster)
#define DEFAULT_TANK_SPEED 100
#define DEFAULT_BULLET_SPEED 20

#define PLAYERLIVE 3  // lives per player (not used yet)
