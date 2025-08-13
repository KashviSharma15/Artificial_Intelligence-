#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Puzzle {
    vector<vector<int>> board;
    int zero_row, zero_col;  
    int heuristic;

    int calculateHeuristic(const vector<vector<int>>& goal) {
        int dist = 0;
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                int val = board[i][j];
                if (val != 0) {
                    for (int x = 0; x < 3; x++){
                        for (int y = 0; y < 3; y++){
                            if (goal[x][y] == val){
                                dist += abs(i - x) + abs(j - y);
                            }
                        }
                    }
                }
            }
        }
        return dist;
    }

    vector<Puzzle> getNeighbors() {
        vector<Puzzle> neighbors;
        vector<pair<int,int>> moves = {{-1,0},{1,0},{0,-1},{0,1}}; 

        for (auto m : moves) {
            int new_r = zero_row + m.first;
            int new_c = zero_col + m.second;
            if (new_r >= 0 && new_r < 3 && new_c >= 0 && new_c < 3){
                Puzzle next = *this;
                swap(next.board[zero_row][zero_col], next.board[new_r][new_c]);
                next.zero_row = new_r;
                next.zero_col = new_c;
                neighbors.push_back(next);
            }
        }
        return neighbors;
    }

    bool isGoal(const vector<vector<int>>& goal) {
        return board == goal;
    }
};

Puzzle hillClimbing(Puzzle start, const vector<vector<int>>& goal) {
    start.heuristic = start.calculateHeuristic(goal);

    while (true) {
        if (start.isGoal(goal)) {
            return start;  
        }

        vector<Puzzle> neighbors = start.getNeighbors();

        Puzzle next_state = start;
        int min_heuristic = start.heuristic;

        for (Puzzle &n : neighbors) {
            n.heuristic = n.calculateHeuristic(goal);
            if (n.heuristic < min_heuristic) {
                min_heuristic = n.heuristic;
                next_state = n;
            }
        }

        if (min_heuristic >= start.heuristic) {
            return start;
        }

        start = next_state;
    }
}

int main() {
    Puzzle start = {
        {{1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}},
        1, 1, 0  
    };

    vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };

    Puzzle result = hillClimbing(start, goal);

    cout << "Result board after hill climbing:\n";
    for (auto &row : result.board) {
        for (int val : row) cout << val << " ";
        cout << "\n";
    }

    if (result.isGoal(goal)) {
        cout << "Goal reached!\n";
    } else {
        cout << "Stopped at local maxima, goal not reached.\n";
    }

    return 0;
}