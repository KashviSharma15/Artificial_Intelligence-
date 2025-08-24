## <u>AIM</u>
A* Search Algorithm for nxn matrics.

---
## Algorithm

1. **State Structure**
   - Maintain a `state` structure with:
     - `id` → unique identifier of the state  
     - `parent_id` → id of the state from which this was generated  
     - `x, y` → coordinates of the cell  
     - `g` → cost from start to current state  
     - `h` → heuristic cost from current to goal (Manhattan distance)  
     - `f` → total cost `f = g + h`

2. **Goal Test**
   - Function `goal_test()` checks if the current state coordinates match the goal coordinates.

3. **Visited Check**
   - Function `visited()` ensures the current state is not already explored in the `closed` list.

4. **Heuristic Function**
   - Function `heuristic()` calculates the Manhattan distance between current state and goal:  
     ```
     h = |x_current - x_goal| + |y_current - y_goal|
     ```

5. **Move Generation**
   - Function `generate_moves()` generates all valid moves in **8 directions**:
     - Top-left, Top, Top-right  
     - Left, Right  
     - Bottom-left, Bottom, Bottom-right  
   - Moves are allowed only if within grid boundaries and the cell is **not blocked**.  
   - **Move Cost**:
     - Horizontal/Vertical → `g = 1.0`  
     - Diagonal → `g = 1.5`
       
6. **A* Search**
   - Maintain an **open list** for states to explore and a **closed list** for visited states.  
   - While open list is not empty:
     1. Select the state with **minimum `f` value**.
     2. If it is the goal → reconstruct the path.
     3. Otherwise:
        - Generate children using `generate_moves()`.
        - If a child is **not visited**, assign `id` and `parent_id`, then add to open list.

7. **Path Reconstruction**
   - Once goal is reached, trace back from `found_goal` to start using `parent_id`.  
   - Print the sequence of coordinates along with `g`, `h`, `f` values.

---

## Time Complexity  
O(maximum branching factor ^ depth of solution) 

---

## Space Complexity
O(maximum branching factor ^ depth of solution)  

---

## Use Cases
- Pathfinding on a grid with obstacles.  
- Understanding **A* search with Manhattan heuristic**.  
- Visualizing 8-directional movement cost calculation and path reconstruction.

---

## Code
```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

struct state {
    int id;
    int parent_id;
    int x, y;
    double g;
    double h;
    double f;
};

bool goal_test(state current, state goal) {
    return (current.x == goal.x && current.y == goal.y);
}

bool visited(vector<state> closed, state cur) {
    for (int idx = 0; idx < (int)closed.size(); idx++) {
        if (closed[idx].x == cur.x && closed[idx].y == cur.y) {
            return true;
        }
    }
    return false;
}

double heuristic(state current, state goal) {
    return abs(current.x - goal.x) + abs(current.y - goal.y);
}

vector<state> generate_moves(state current, int &id_counter, state goal, int n, vector<vector<int>> &board) {
    vector<state> moves;
    int dir_x[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dir_y[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int k = 0; k < 8; k++) {
        int new_x = current.x + dir_x[k];
        int new_y = current.y + dir_y[k];

        if (new_x >= 0 && new_x < n && new_y >= 0 && new_y < n && board[new_x][new_y] == 0) {
            state next;
            next.x = new_x;
            next.y = new_y;
            next.id = id_counter++;
            next.parent_id = current.id;

            if (dir_x[k] == 0 || dir_y[k] == 0) next.g = current.g + 1.0;
            else next.g = current.g + 1.5;

            next.h = heuristic(next, goal);
            next.f = next.g + next.h;

            moves.push_back(next);
        }
    }

    return moves;
}

int main() {
    int n;
    cout << "Enter board size n: ";
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n, 0));

    int start_x, start_y, goal_x, goal_y;
    cout << "Enter start cell (row col): ";
    cin >> start_x >> start_y;
    cout << "Enter destination cell (row col): ";
    cin >> goal_x >> goal_y;

    int blocks;
    cout << "Enter number of blocked cells: ";
    cin >> blocks;
    cout << "Enter blocked cells (row col):\n";
    for (int i = 0; i < blocks; i++) {
        int bx, by;
        cin >> bx >> by;
        board[bx][by] = 1;
    }

    int id_counter = 1;
    state start, goal;
    start.x = start_x; start.y = start_y;
    start.id = id_counter++;
    start.parent_id = -1;
    start.g = 0;
    start.h = heuristic(start, goal);
    start.f = start.g + start.h;

    goal.x = goal_x;
    goal.y = goal_y;

    vector<state> open;
    vector<state> closed;
    open.push_back(start);

    bool found = false;
    state found_goal;

    while (!open.empty()) {
        int best_idx = 0;
        for (int i = 1; i < (int)open.size(); i++) {
            if (open[i].f < open[best_idx].f) best_idx = i;
        }

        state current = open[best_idx];
        open.erase(open.begin() + best_idx);

        if (visited(closed, current)) continue;
        closed.push_back(current);

        if (goal_test(current, goal)) {
            found = true;
            found_goal = current;
            break;
        }

        vector<state> children = generate_moves(current, id_counter, goal, n, board);
        for (int i = 0; i < (int)children.size(); i++) {
            if (!visited(closed, children[i])) open.push_back(children[i]);
        }
    }

    if (found) {
        vector<state> path;
        state cur = found_goal;
        while (true) {
            path.push_back(cur);
            if (cur.parent_id == -1) break;
            for (int i = 0; i < (int)closed.size(); i++) {
                if (closed[i].id == cur.parent_id) {
                    cur = closed[i];
                    break;
                }
            }
        }

        cout << "Path found:\n";
        for (int p = (int)path.size() - 1; p >= 0; p--) {
            cout << "(" << path[p].x << "," << path[p].y << ") g=" 
                << path[p].g << " h=" << path[p].h << " f=" << path[p].f << "\n";
        }
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
```

---
## Output
<img width="312" height="186" alt="Screenshot 2025-08-24 at 9 36 33 PM" src="https://github.com/user-attachments/assets/ce1bb4df-c278-41bd-a4b5-0bd30d06dcbb" />


