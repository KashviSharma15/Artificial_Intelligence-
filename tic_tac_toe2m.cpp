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
