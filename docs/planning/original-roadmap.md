# 🎮 LED Tank Battle — Original Development Plan

> **Project:** Two-player tank game on a 16×32 LED screen (8 × MAX7219 matrices)
> **Platform:** Arduino
> **Language:** C++ (OOP)
> **Goal:** A professional project for GitHub and my CV

*This is the plan I wrote before starting. The final code follows it closely but not exactly (for example, `Bullet` got its own files and the game class is called `Game`).*

---

## Planned file structure

```
TankBattle/
│
├── TankBattle.ino          ← the only entry point
│
├── Config.h                ← all constants and definitions
│
├── Matrix.h / Matrix.cpp   ← addressing and coordinate layer
├── Display.h / Display.cpp ← drawing layer (LedControl wrapper)
│
├── InputManager.h / InputManager.cpp  ← button handling
│
├── Tank.h / Tank.cpp       ← Tank class + Bullet class
├── Barrier.h / Barrier.cpp ← barrier class
├── PowerUp.h / PowerUp.cpp ← PowerUpType enum + PowerUp class
│
└── Game.h / Game.cpp       ← GameEngine (connects everything)
```

---

## Phase 1 — Foundation

**Goal:** working screen + correct coordinates + responsive buttons

### `Config.h`
- [ ] Define DIN, CLK, CS pins
- [ ] Define button pins (left, right, fire) for player 1 and player 2
- [ ] `#define MATRIX_COUNT 8`
- [ ] `#define SCREEN_WIDTH 16`
- [ ] `#define SCREEN_HEIGHT 32`
- [ ] Default speed constants for tanks and bullets

### `Matrix.h / Matrix.cpp`
- [ ] `struct Coord { int x; int y; }`
- [ ] `bool inBounds(int x, int y)` — checks that a point is on the screen
- [ ] `int getMatrixIndex(int x, int y)` — returns the module number (0–7)
- [ ] `void toLocalCoord(int x, int y, int &lx, int &ly)` — converts to coordinates inside one module

> 💡 My existing `pixsel_led` code moves here first

### `Display.h / Display.cpp`
- [ ] `DisplayManager` class
- [ ] `void begin()` — initialize all modules
- [ ] `void setPixel(int x, int y, bool state)`
- [ ] `void clearAll()`
- [ ] `void clearRegion(int x1, int y1, int x2, int y2)`
- [ ] `void drawRect(int x, int y, int w, int h, bool state)`

### `InputManager.h / InputManager.cpp`
- [ ] `InputManager` class
- [ ] `void begin()` — `pinMode` for every button
- [ ] `bool isPressed(uint8_t pin)` — read with debounce, no `delay()`
- [ ] Use `millis()` instead of `delay()` for debounce

### `TankBattle.ino`
- [ ] Only includes
- [ ] Empty `setup()` and `loop()` (filled in later)

**✅ Phase 1 test:**
Light some pixels by hand through `DisplayManager` and check the coordinates on the real screen.

---

## Phase 2 — Tank and movement

**Goal:** a tank that moves left and right smoothly

### `Tank.h / Tank.cpp`

#### `Bullet` class
- [ ] `int x, y` — bullet position
- [ ] `int direction` — `+1` up, `-1` down
- [ ] `int speed` — bullet speed (can be changed by a power-up)
- [ ] `bool active` — is the bullet flying?
- [ ] `void update()` — move one step
- [ ] `void draw(DisplayManager &d)` / `void erase(DisplayManager &d)`
- [ ] `bool isOutOfBounds()` — has it left the screen?

#### `Tank` class
- [ ] `int x` — horizontal position
- [ ] `int lives` — number of lives (start with 3)
- [ ] `int speed` — movement speed
- [ ] `int side` — `0` bottom, `1` top
- [ ] `Bullet bullets[3]` — at most 3 active bullets
- [ ] `void moveLeft()` / `void moveRight()`
- [ ] `void shoot()`
- [ ] `void updateBullets()`
- [ ] `void draw(DisplayManager &d)` / `void erase(DisplayManager &d)`
- [ ] `void takeDamage(int dmg)`
- [ ] `bool isAlive()`
- [ ] `void applyPowerUp(PowerUpType type)` ← finished in Phase 4

**✅ Phase 2 test:**
One tank moves with the buttons and fires a bullet that travels forward and disappears.

---

## Phase 3 — Barriers

**Goal:** barriers in the middle of the screen that absorb bullets

### `Barrier.h / Barrier.cpp`
- [ ] `Barrier` class
- [ ] `int x, y` — position
- [ ] `int health` — hit points (e.g. 3 hits)
- [ ] `bool active`
- [ ] `void draw(DisplayManager &d)`
- [ ] `void erase(DisplayManager &d)`
- [ ] `void takeDamage()` — lose health, erase and redraw
- [ ] `bool isDestroyed()`
- [ ] `bool checkCollision(Bullet &b)` — was it hit?

**✅ Phase 3 test:**
A bullet hits a barrier and disappears; the barrier disappears after N hits.

---

## Phase 4 — Random power-ups

**Goal:** gifts that appear on the screen and help whoever gets them first

### `PowerUp.h / PowerUp.cpp`

#### `PowerUpType` enum
```cpp
enum PowerUpType {
  PU_NONE = 0,
  PU_EXTRA_LIFE,     // extra life
  PU_SPEED_BOOST,    // faster tank
  PU_BULLET_SPEED,   // faster bullets
  PU_SHIELD          // temporary shield
};
```

#### `PowerUp` class
- [ ] `int x, y`
- [ ] `PowerUpType type`
- [ ] `bool active`
- [ ] `unsigned long spawnTime` — when it appeared
- [ ] `void spawn(DisplayManager &d)` — appear at a random position
- [ ] `void draw(DisplayManager &d)` — different shape for each type
- [ ] `void erase(DisplayManager &d)`
- [ ] `bool checkCollision(Tank &t)` — did a tank take it?
- [ ] `bool isExpired()` — has its time run out? (e.g. 5 seconds)

#### In `Tank` — finish `applyPowerUp`:
- [ ] `PU_EXTRA_LIFE` → increase `lives`
- [ ] `PU_SPEED_BOOST` → shorter movement delay
- [ ] `PU_BULLET_SPEED` → increase `bullet.speed`
- [ ] `PU_SHIELD` → temporary shield using `millis()`

**✅ Phase 4 test:**
A gift appears, a tank passes over it, and its behavior changes.

---

## Phase 5 — GameEngine and full integration

**Goal:** connect everything into one complete game

### `Game.h / Game.cpp`

#### `GameState` enum
```cpp
enum GameState {
  STATE_MENU,
  STATE_PLAYING,
  STATE_PAUSED,
  STATE_GAME_OVER
};
```

#### `GameEngine` class
- [ ] Owns: `Tank player1, player2`
- [ ] Owns: `Barrier barriers[4]`
- [ ] Owns: `PowerUp powerUps[2]`
- [ ] Owns: `GameState state`
- [ ] Owns: `DisplayManager display`
- [ ] Owns: `InputManager input`
- [ ] `void setup()` — initialize everything
- [ ] `void loop()` — called from the main `loop()`
- [ ] `void update()` — move tanks, bullets and power-ups
- [ ] `void checkCollisions()` — detect every collision:
  - bullet → enemy tank
  - bullet → barrier
  - tank → power-up
- [ ] `void render()` — draw everything
- [ ] `void spawnPowerUp()` — spawn a random power-up from time to time
- [ ] `void checkWinCondition()` — has a player run out of lives?
- [ ] `void showGameOver()` — end-of-game message

### `TankBattle.ino` (final version)
```cpp
#include "Game.h"
GameEngine game;
void setup() { game.setup(); }
void loop()  { game.loop();  }
```

**✅ Phase 5 test:**
A full game between two players; the winner is the last one with lives left.

---

## Phase 6 — Polish and extras

**Goal:** make the project look professional on GitHub

- [ ] Start screen (show "TANK WAR" on the LEDs)
- [ ] Score counter (on Serial or an extra screen)
- [ ] Simple buzzer sound on hit
- [ ] Save the high score in EEPROM
- [ ] Visual explosion on death (blinking pixels)
- [ ] Professional README.md with photos and a wiring diagram
- [ ] `/** Doxygen */` comments on every function
- [ ] `schematic.png` wiring diagram

---

## Code rules

```
✔ Always use millis() — no delay() in loop()
✔ Every class in its own .h and .cpp
✔ Constants only in Config.h
✔ No global variables outside classes
✔ No function longer than 20 lines
✔ Test every phase on real hardware before moving on
```

---

## Dependency order (bottom to top)

```
Config.h
    ↓
Matrix ← Display
    ↓
InputManager
    ↓
Tank (Bullet) ← Barrier ← PowerUp
    ↓
GameEngine
    ↓
TankBattle.ino
```
