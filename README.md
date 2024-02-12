# Battleships
A console application for battleships match between two players, player and a bot or two bots.

## Controls
### Blocks
- `[state] ... [state]` – state commands
- `[playerA] ... [playerA]` – player A commands
- `[playerB] ... [playerB]` – player B commands

### Commands
#### State commands
- `PRINT x`, where
  - `x` – version (`0`/`1`);
- `SET_FLEET p a1 a2 a3 a4`, where:
  - `p` – player, e.g. `A`,
  - `a1`, `a2`, `a3`, `a4` – numbers of ships of categories: CAR, BAT, CRU, DES;
- `NEXT_PLAYER p`, where:
  - `p` – player, e.g. `A`;
- `BOARD_SIZE y x`;
- `INIT_POSITION p y1 x1 y2 x2`;
- `REEF y x`;
- `SHIP p y x d i c a1...al`, where:
  - `d` – direction of the ship `N`/`W`/`S`/`E`,
  - `i` – index of the ship in the given category,
  - `c` – category of the ship,
  - `a1...al` – states (`1`/`0`) of each segment of the ship;
- `EXTENDED_SHIPS`;
- `SET_AI_PLAYER p`;
- `SRAND x`;
- `SAVE`

#### Player commands
- `PLACE_SHIP y x d i c`;
- `SHOOT y x`;
- `MOVE i c x`, where:
  - `x` – direction (`F`/`L`/`R`);
- `SHOOT i c y x`;
- `SPY i y x`, where:
  - `i` – index of the CAR-category ship sending the spy;
- `PRINT x`
