/*
 * Matrix.cpp - maps screen coordinates to the MAX7219 chain
 *
 * Module number on the chain for each part of the screen:
 *
 *              x 0-7    x 8-15
 *   y  0-7       7        3
 *   y  8-15      6        2
 *   y 16-23      5        1
 *   y 24-31      4        0
 */
#include "Config.h"

// True if (x, y) is inside the 16 x 32 screen
bool inBounds(int x, int y) {

    if ((x < 0 || x >= SCREEN_WIDTH) || (y < 0 || y >= SCREEN_HEIGHT)) {
        return false;
    } else {
        return true;
    }
}

// Return the module number (0-7) that contains pixel (x, y)
int getMatrixIndex(int x, int y) {
    int matrix = 7;             // top-left module

    if (x > 7) {                // right column
        matrix -= 4;
    }
    if (y > 7 && y < 16) {      // 2nd row
        matrix -= 1;
    }
    else if (y > 15 && y < 24) { // 3rd row
        matrix -= 2;
    }
    else if (y >= 24) {         // 4th row
        matrix -= 3;
    }

    return matrix;
}

// Convert a screen coordinate to a coordinate inside one 8x8 module
void toLocalCoord(int x, int y, int &lx, int &ly) {
    if (x > 7) {
        x -= 8;
    }

    if (y > 7 && y < 16) {
        y -= 8;
    }
    else if (y > 15 && y < 24) {
        y -= 16;
    }
    else if (y >= 24) {
        y -= 24;
    }

    lx = x;
    ly = y;
}
