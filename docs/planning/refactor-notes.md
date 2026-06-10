# Refactor Notes — Lives and Match Wins (planned, not implemented)

The idea: each player gets **3 hearts per match**, and the game keeps a
**total match-win counter** that stays until the board is turned off.
Scores and messages would be shown on a small OLED screen.

---

## File 1: `UIManager.h` / `UIManager.cpp` (OLED screen manager)

**Class:** `UIManager`

**Public functions:**

- `void drawScore(int wins1, int wins2, int hearts1, int hearts2);`
  Shows each player's match wins and remaining hearts.
  Example: `P1: ♥♥♥ [1] - P2: ♥♡♡ [0]`

- `void drawMessage(const char* msg);`
  Shows a short info message, for example `"P1 lost a life!"` when someone is hit.

## File 2: `Game.h` (new state and control)

**Private variables:**

- `int p1Hearts, p2Hearts;` — hearts in the current match. Start at 3 in each new match.
- `int p1MatchWins, p2MatchWins;` — total matches won. Start at 0 when the game is turned on.

**Private functions:**

- `void resetRound();` — only puts the tanks back at their start positions and removes bullets.
  Does **not** touch hearts or total wins. Called when someone is hit.
- `void resetMatch();` — sets both players' hearts to 3 and calls `resetRound()`.
  Called when a new match starts.

## File 3: `Game.cpp` (logic to add)

**Inside the collision check** (example: player 1's bullet hits player 2's tank):

1. Remove the bullet, play the explosion animation and the explosion sound.
2. `p2Hearts--;` (player 2 loses one heart)
3. **If** `p2Hearts <= 0`:
   - `p1MatchWins++;` (player 1 wins the match)
   - Set the state to `STATE_GAMEOVER` and play the game-over sound.
4. **Else**:
   - Show `ui.drawMessage("P2 hit!");` on the OLED.
   - Wait 1 second so the players can see what happened.
   - Call `resetRound();` to put the tanks back and continue the match.

**Game loop flow:**

- **`STATE_MENU`** — total wins stay the same. Pressing any button calls `resetMatch()`
  (hearts back to 3) and switches to `STATE_PLAYING`.
- **`STATE_PLAYING`** — the OLED is updated all the time with
  `ui.drawScore(p1MatchWins, p2MatchWins, p1Hearts, p2Hearts);`. Collision checks happen here.
- **`STATE_GAMEOVER`** — the OLED shows the winner (`"P1 WINS!"`). Pressing any button goes
  back to `STATE_MENU`, or calls `resetMatch()` directly to start a new match.
