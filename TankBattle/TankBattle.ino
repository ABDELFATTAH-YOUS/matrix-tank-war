/*
 * Matrix Tank War - main sketch
 *
 * Creates the display, input and game objects and runs the game loop.
 * A 16x2 I2C LCD shows the score of both players.
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Config.h"
#include "Display.h"
#include "InputManager.h"
#include "Game.h"

// 16x2 LCD at I2C address 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

DisplayManager matrixDisplay;  // 16x32 LED matrix screen
InputManager input;            // player buttons
Game game;                     // game rules and state

// Last scores written to the LCD (-1 forces the first update)
int lastP1 = -1;
int lastP2 = -1;

void setup() {
    matrixDisplay.begin();
    input.begin();

    // Start I2C: SDA = PB7, SCL = PB6
    Wire.begin(PB7, PB6);
    lcd.begin();
    lcd.backlight();
    lcd.clear();
}

// Redraw the LCD only when a score changes (LCD writes are slow)
void updateLCD(int p1, int p2) {
    if (p1 != lastP1 || p2 != lastP2) {
        lcd.setCursor(0, 0);
        lcd.print("P1: "); lcd.print(p1);
        lcd.print("      P2: "); lcd.print(p2);

        // Keep the second line empty
        lcd.setCursor(0, 1);
        lcd.print("                ");

        lastP1 = p1;
        lastP2 = p2;
    }
}

void loop() {
    game.update(matrixDisplay, input);

    // Only the scores go to the LCD (event messages are turned off)
    updateLCD(game.getP1Score(), game.getP2Score());
}
