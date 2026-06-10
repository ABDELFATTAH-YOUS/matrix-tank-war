/*
 * Matrix.h - converts screen coordinates to MAX7219 module coordinates
 */
#pragma once
#include <Arduino.h>

// A point on the screen (not used yet)
struct Coord {
    int x;
    int y;
};

bool inBounds(int x, int y);                             // is (x, y) on the screen?
int getMatrixIndex(int x, int y);                        // which module (0-7) holds (x, y)
void toLocalCoord(int x, int y, int &lx, int &ly);       // (x, y) inside that module (0-7)
