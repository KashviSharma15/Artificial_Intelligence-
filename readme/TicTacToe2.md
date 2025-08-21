## <u>AIM</u>  
To implement a Tic-Tac-Toe game using modified 2nd approach.

---

## Algorithm

1. **Board Representation**  
   - Use an integer array `BOARD[10]` (1-based indexing) where:  
     - `2` → empty  
     - `3` → computer's move ('X')  
     - `5` → human's move ('O')

2. **Magic Square Mapping**  
   - Use a `magicSquare[10]` array that maps board positions to a magic square numbering (1 to 9) with sums of any winning line equal to 15.  
   - Positions mapped as:  
     `{0, 8, 3, 4, 1, 5, 9, 6, 7, 2}` (index 0 unused)

3. **Display Board**  
   - Print the board using symbols:  
     - `'_'` for empty, `'X'` for computer, `'O'` for human.

4. **Check Possible Winning Move (`POSSWIN`)**  
   - For a given player, check all pairs of positions occupied by that player.  
   - Calculate the missing magic square number to reach 15.  
   - If the corresponding position is empty, return that position as a winning/blocking move.

5. **Make a Move (`GO`)**  
   - Place the player's mark on the board if the position is valid and empty.

6. **Check Win Condition**  
   - Use predefined winning lines.  
   - Compute product of values at these positions:  
     - `27` (3*3*3) means computer wins  
     - `125` (5*5*5) means human wins.

7. **Check Draw**  
   - Game is a draw if no empty positions remain and no winner.

8. **Take Center or Sides (`MAKE2`)**  
   - If center (position 5) is free, take it.  
   - Else take one of the sides (positions 2, 4, 6, 8).

9. **Game Loop**  
   - Alternates between human and computer turns.  
   - Human inputs a valid move.  
   - Computer chooses a move based on:  
     - Winning move if available.  
     - Block opponent’s winning move.  
     - Take center or sides.  
     - Take any available spot otherwise.  
   - After each move, check for win or draw.  
   - End game on win/draw.

---

## Time Complexity  
- Move decisions involve iterating through positions and pairs → \( O(n^2) \) where \( n=9 \), practically constant.

---

## Space Complexity  
- Uses fixed arrays for board and magic square → \( O(1) \).


## Use Cases  
- Demonstrates an alternate method (magic square) for move calculation in Tic-Tac-Toe.  
- Illustrates use of mathematical properties (magic square sums) for game logic.

## Space Complexity  
- Memory usage depends on the number of visited states and the size of the priority queue.

---

## Use Cases  
- Demonstrates how heuristic information can guide search in a finite state problem.  
- Illustrates state representation, successor generation, and solution path reconstruction.

---

## Code 

```cpp
#include <iostream>
using namespace std;

int BOARD[10];  

int magicSquare[10] = {0, 8, 3, 4,
                        1, 5, 9,
                        6, 7, 2};  

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

int POSSWIN(int player) {
    for (int i = 1; i <= 9; i++) {
        if (BOARD[i] == player) {
            for (int j = i + 1; j <= 9; j++) {
                if (BOARD[j] == player) {
                    int missing = 15 - (magicSquare[i] + magicSquare[j]);
                    for (int k = 1; k <= 9; k++) {
                        if (magicSquare[k] == missing && BOARD[k] == 2)
                            return k;
                    }
                }
            }
        }
    }
    return 0;
}

void GO(int pos, int player) {
    if (pos >= 1 && pos <= 9 && BOARD[pos] == 2)
        BOARD[pos] = player;
}

bool checkWin(int player) {
    int productTarget = (player == 3) ? 27 : 125;  
    int WIN_LINES[8][3] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}
    };
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

int MAKE2() {
    if (BOARD[5] == 2) return 5;
    int sides[] = {2, 4, 6, 8};
    for (int pos : sides) {
        if (BOARD[pos] == 2) return pos;
    }
    return 0;
}

int main() {
    for (int i = 1; i <= 9; i++) BOARD[i] = 2; 

    cout << "You are O. Computer is X." << endl;
    displayBoard();

    int turn = 5; 
    while (true) {
        if (turn == 5) {  
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

            turn = 3; 
        } else { 
            int CompMove = POSSWIN(3);  
            if (!CompMove) CompMove = POSSWIN(5);  
            if (!CompMove) CompMove = MAKE2();     
            if (!CompMove) { 
                for (int i = 1; i <= 9; i++) {
                    if (BOARD[i] == 2) {
                        CompMove = i;
                        break;
                    }
                }
            }
            cout << "Computer moves at position: " << CompMove << endl;
            GO(CompMove, 3);
            displayBoard();

            if (checkWin(3)) {
                cout << "Computer won!" << endl;
                break;
            }
            if (isDraw()) {
                cout << "Game is a draw!" << endl;
                break;
            }
            turn = 5; 
        }
    }

    cout << "Game Over!" << endl;
    return 0;
}
