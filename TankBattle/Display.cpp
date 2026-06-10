#include "Display.h"
#include "Matrix.h"

// Wake up every module, set brightness and clear it
void DisplayManager::begin() {
    for(int index = 0; index < MATRIX_COUNT; index++) {
        lc.shutdown(index, false);
        lc.setIntensity(index, LIGHT);
        lc.clearDisplay(index);
    }
}

// Set one pixel. Pixels outside the screen are ignored.
void DisplayManager::setPixel(int x, int y, bool state) {
    if (!inBounds(x, y)) return;

    int matrix = getMatrixIndex(x, y);
    int lx = 0;
    int ly = 0;

    toLocalCoord(x, y, lx, ly);
    lc.setLed(matrix, lx, ly, state);
}

void DisplayManager::clearAll() {
    for(int index = 0; index < MATRIX_COUNT; index++) {
        lc.clearDisplay(index);
    }
}

// Turn off every pixel from (x1, y1) to (x2, y2), both included
void DisplayManager::clearRegion(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            setPixel(i, j, false);
        }
    }
}

// Fill a w x h box with its top-left corner at (x, y)
void DisplayManager::drawRect(int x, int y, int w, int h, bool state) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            setPixel(x + i, y + j, state);
        }
    }
}
