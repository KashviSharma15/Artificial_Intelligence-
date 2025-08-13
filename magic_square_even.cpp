#include <iostream>
#include <vector>
using namespace std;

void generateEvenMagicSquare(int n) {
    if (n < 4 || n % 2 != 0) {
        cout << "Enter an even number >= 4.\n";
        return;
    }

    vector<vector<int>> square(n, vector<int>(n));

    if (n % 4 == 0) {
        int num = 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                square[i][j] = ((i % 4 == j % 4) || ((i % 4 + j % 4) == 3)) ? n * n + 1 - num++ : num++;
    } else {
        int half = n / 2, subSize = half * half;
        vector<vector<int>> sub(half, vector<int>(half));

        int i = 0, j = half / 2;
        for (int num = 1; num <= subSize; num++) {
            sub[i][j] = num;
            int ni = (i - 1 + half) % half;
            int nj = (j + 1) % half;
            if (sub[ni][nj] != 0) i = (i + 1) % half;
            else { i = ni; j = nj; }
        }

        for (int r = 0; r < half; r++)
            for (int c = 0; c < half; c++) {
                int val = sub[r][c];
                square[r][c] = val;
                square[r + half][c + half] = val + subSize;
                square[r][c + half] = val + 2 * subSize;
                square[r + half][c] = val + 3 * subSize;
            }

        int k = (half - 1) / 2;
        for (int r = 0; r < half; r++)
            for (int c = 0; c < k; c++)
                swap(square[r][c], square[r + half][c]);
        for (int r = 0; r < half; r++)
            for (int c = n - k + 1; c < n; c++)
                swap(square[r][c], square[r + half][c]);
    }

    cout << "Magic square of size " << n << ":\n";
    for (auto &row : square) {
        for (int val : row) cout << val << "\t";
        cout << "\n";
    }
}

int main() {
    int n;
    cout << "Enter an even number for Magic Square: ";
    cin >> n;
    generateEvenMagicSquare(n);
    return 0;
}
