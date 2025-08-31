## <u>AIM</u>
To implement a **Tic-Tac-Toe** game with an **unbeatable AI** using the `Minimax` algorithm.

---

## <u>Algorithm</u>

1. **Board Representation**
   - Use a 1D array `BOARD[10]` (index `1–9`) for the 3×3 grid.
   - Values: `2` = empty, `3` = computer (`X`), `5` = human (`O`).
   - Winning combinations stored in `WIN_LINES[8][3]`.

2. **Display Board**
   - Print the current state of the board with symbols `X`, `O`, or `_` for empty.

3. **Move Generation**
   - **Human Move:** Input validated for empty cells.
   - **Computer Move:** Use `Minimax` algorithm to select the optimal move.
   - **Special Move (`MAKE2`)**: Picks center first or sides if center is occupied.

4. **Winning & Draw Checks**
   - `checkWin(player)` determines if a player has won.
   - `isDraw()` checks if all cells are filled without a winner.

5. **Minimax Algorithm**
   - Recursively evaluates all possible moves.
   - `isMaximizing = true` → computer’s turn, maximize score.
   - `isMaximizing = false` → human’s turn, minimize score.
   - Terminal states: win (`+1`), lose (`-1`), draw (`0`).

6. **Gameplay Loop**
   - Alternate human and computer turns.
   - Display board after each move.
   - Announce winner or draw when the game ends.

---

## <u>Time Complexity</u>
- Worst case: `O(9!)` due to exhaustive evaluation of all moves by `Minimax`.

---

## <u>Space Complexity</u>
- `O(9)` for `BOARD` array plus recursion stack in `Minimax`.

---

## <u>Use Cases</u>
- Demonstrates **game AI** using `Minimax`.
- Ensures **unbeatable computer strategy** for small games like `Tic-Tac-Toe`.
- Can be extended to other **games** like chess.

  ## <u>Code</u>
  ```cpp
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int BOARD[10]; 
int WIN_LINES[8][3] = {
    {1, 2, 3}, 
    {4, 5, 6},
    {7, 8, 9},
    {1, 4, 7}, 
    {2, 5, 8},
    {3, 6, 9},
    {1, 5, 9}, 
    {3, 5, 7}
};

void displayBoard() {
    for (int i = 1; i <= 9; i++) {
        char symbol;
        if (BOARD[i] == 2) symbol = '_';
        else if (BOARD[i] == 3) symbol = 'X';
        else symbol = 'O';
        cout << symbol << " ";
        if (i % 3 == 0) cout << endl;
    }
    cout << endl;
}

int MAKE2() {
    if (BOARD[5] == 2) return 5; 
    int sides[] = {2, 4, 6, 8};
    for (int pos : sides) {
        if (BOARD[pos] == 2) return pos;
    }
    return 0;
}

int POSSWIN(int player) {
    int targetProduct = (player == 3) ? 18 : 50; 
    for (int i = 0; i < 8; i++) {
        int p1 = WIN_LINES[i][0], p2 = WIN_LINES[i][1], p3 = WIN_LINES[i][2];
        int prod = BOARD[p1] * BOARD[p2] * BOARD[p3];
        if (prod == targetProduct) {
            if (BOARD[p1] == 2) return p1;
            if (BOARD[p2] == 2) return p2;
            if (BOARD[p3] == 2) return p3;
        }
    }
    return 0;
}

void GO(int position, int player) {
    if (position >=1 && position <=9 && BOARD[position] == 2) BOARD[position] = player;
}

bool checkWin(int player) {
    int productTarget = (player == 3) ? 27 : 125; 
    for (int i = 0; i < 8; i++) {
        int p1 = WIN_LINES[i][0], p2 = WIN_LINES[i][1], p3 = WIN_LINES[i][2];
        int prod = BOARD[p1] * BOARD[p2] * BOARD[p3];
        if (prod == productTarget) return true;
    }
    return false;
}

bool isDraw() {
    for (int i = 1; i <= 9; i++) {
        if (BOARD[i] == 2) return false;
    }
    return true;
}

int minimax(bool isMaximizing) {
    if (checkWin(3)) return +1;
    if (checkWin(5)) return -1;
    if (isDraw()) return 0;

    if (isMaximizing) {
        int best = numeric_limits<int>::min();
        for (int i = 1; i <= 9; i++) {
            if (BOARD[i] == 2) {
                BOARD[i] = 3;
                best = max(best, minimax(false));
                BOARD[i] = 2;
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max();
        for (int i = 1; i <= 9; i++) {
            if (BOARD[i] == 2) {
                BOARD[i] = 5;
                best = min(best, minimax(true));
                BOARD[i] = 2;
            }
        }
        return best;
    }
}

int generate_move() {
    int bestVal = numeric_limits<int>::min();
    int bestMove = -1;

    for (int i = 1; i <= 9; i++) {
        if (BOARD[i] == 2) {
            BOARD[i] = 3;
            int moveVal = minimax(false);
            BOARD[i] = 2;
            if (moveVal > bestVal) {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

int main() {
    for (int i = 1; i <= 9; i++) BOARD[i] = 2;

    cout << "You are O. Computer is X." << endl;
    displayBoard();

    while (true) {
        int humanMove;
        cout << "Enter your move (1-9): ";
        while (true) {
            cin >> humanMove;
            if (humanMove >= 1 && humanMove <= 9 && BOARD[humanMove] == 2) {
                GO(humanMove, 5); 
                break;
            } else {
                cout << "Invalid move, try again: ";
            }
        }
        displayBoard();

        if (checkWin(5)) {
            cout << "You won!" << endl;
            break;
        }
        if (isDraw()) {
            cout << "Game is a draw!" << endl;
            break;
        }

        int CompMove = generate_move();
        cout << "Computer moves at position: " << CompMove << endl;
        GO(CompMove, 3);
        displayBoard();

        if (checkWin(3)) {
            cout << "Computer won! " << endl;
            break;
        }
        if (isDraw()) {
            cout << "Game is a draw!" << endl;
            break;
        }
    }

    cout << "Game Over!" << endl;
    return 0;
}

  ```
  ## <u>Output</u>
