## <u>AIM</u>  
To implement a Tic-Tac-Toe game using Approach 2.

---

## Algorithm

1. *Board Representation*  
   - Explain how the board is stored  
   - Example: 2 → empty, 3 → X, 5 → O

2. *Display Board*  
   - Mention how the board is displayed  
   - Example: '_' for empty, 'X' for computer, 'O' for human

3. **Winning Move Check (POSSWIN)**  
   - Describe the logic for checking possible winning moves 
   - You can use math notation like:  
     - If product = 18 → computer wins next  
     - If sum = $15$ → player wins

4. **Make a Move (GO)**  
   - Explain move placement logic  

5. *Check Win Condition*  
   - Add conditions in bullet or math form

6. *Check Draw*  
   - Add logic here

7. **Helper Function (e.g., MAKE2)**  
   - Describe center/sides logic

8. *Game Loop*  
   - Describe turn-by-turn logic (computer vs human)

---

## Time Complexity  
- For each move, checks a constant number of winning lines.  
- *Time Complexity:* O(1)  

---

## Space Complexity  
- Uses fixed arrays for board/magic square.  
- *Space Complexity:* O(1)  

---

## Use Cases  
## Use Cases  
- *Educational Purpose:* Helps students learn how algorithms can be applied to simple games.  
- *Game Development:* Can be used as a base for building simple AI opponents in Tic-Tac-Toe.  

---

## Code
```cpp
#include <iostream>
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

void GO(int pos, int player) {
    if (pos >=1 && pos <=9 && BOARD[pos] == 2) BOARD[pos] = player;
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

        int aiMove = POSSWIN(3); 
        if (!aiMove) aiMove = POSSWIN(5); 
        if (!aiMove) aiMove = MAKE2(); 
        if (!aiMove) {
            for (int i = 1; i <= 9; i++) {
                if (BOARD[i] == 2) {
                    aiMove = i;
                    break;
                }
            }
        }
        cout << "AI moves at position: " << aiMove << endl;
        GO(aiMove, 3);
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
---

## Output
 <img width="447" height="727" alt="Screenshot 2025-08-24 at 9 40 03 PM" src="https://github.com/user-attachments/assets/990a8591-3df9-4156-b3ab-b7f06947804c" />

