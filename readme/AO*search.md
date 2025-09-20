## AIM
To implement **AO\* (And-Or) Search** 

---

## Algorithm

1. **State Structure**  
   Each state is represented as a `struct State`:
   - `x, y` → coordinates of the node  
   - `g` → cost from start to current node  
   - `h` → heuristic estimate to goal (Manhattan distance)  
   - `f` → total estimated cost (`f = g + h`)  
   - `solved` → true if goal reached  
   - `isAndNode` → true if AND node (used in generalized AO\* problems)  
   - `children` → vector of pointers to child states

2. **Heuristic Function**  
   - `heuristic(State* s, State* goal)` calculates **Manhattan distance** from the current state to the goal.

3. **AO\* Search Function**  
   - `AOStar()` recursively evaluates nodes:  
     - Skips nodes that are already solved or visited  
     - Generates all valid successors by moving **Up, Down, Left, Right** in the 5×5 grid  
     - Updates `f` values as `g + min(child_f)` for OR nodes  
     - Marks node as `solved` if goal reached

4. **Visited Set**  
   - Prevents revisiting nodes using a `set<pair<int,int>>` of coordinates.

5. **Memory Management**  
   - All dynamically allocated states are stored in `allStates` and deleted at the end to avoid memory leaks.

---

## Time Complexity
- In the worst case, AO\* explores **all reachable nodes**, giving **O(b^d)** complexity, where `b` is branching factor (up to 4) and `d` is maximum depth.  
- AO\* uses heuristic estimates to prune unnecessary paths, improving efficiency over naive search.

---

## Code

```cpp
#include <iostream>
#include <vector>
#include <cmath>
#include <set>
using namespace std;

struct State {
    int x, y;
    double g, h, f;
    bool solved;
    bool isAndNode;
    vector<State*> children;
};

double heuristic(State* s, State* goal) {
    return abs(s->x - goal->x) + abs(s->y - goal->y);
}

void AOStar(State* node, State* goal, vector<State*>& allStates, set<pair<int,int>>& visited) {
    if (node->solved) return;
    if (visited.count({node->x, node->y})) return;
    visited.insert({node->x, node->y});

    vector<State*> successors;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    for (int k = 0; k < 4; k++) {
        int nx = node->x + dx[k];
        int ny = node->y + dy[k];
        if (nx >= 0 && ny >= 0 && nx < 5 && ny < 5) {
            State* child = new State{nx, ny, node->g + 1, 0, 0, false, false};
            child->h = heuristic(child, goal);
            child->f = child->g + child->h;
            successors.push_back(child);
            allStates.push_back(child);
            node->children.push_back(child);
        }
    }

    if (successors.empty()) {
        node->f = 1e9; 
        return;
    }

    double minCost = 1e9;
    for (State* child : node->children) {
        AOStar(child, goal, allStates, visited);
        minCost = min(minCost, child->f);
    }

    node->f = node->g + minCost;
    if (node->x == goal->x && node->y == goal->y) node->solved = true;
}

int main() {
    int sx, sy, gx, gy;
    cout << "Enter start coordinates (x y): ";
    cin >> sx >> sy;
    cout << "Enter goal coordinates (x y): ";
    cin >> gx >> gy;

    State* start = new State{sx, sy, 0, 0, 0, false, false};
    State* goal  = new State{gx, gy, 0, 0, 0, false, false};

    vector<State*> allStates;
    allStates.push_back(start);

    set<pair<int,int>> visited;
    AOStar(start, goal, allStates, visited);

    cout << "Final cost from start to goal: " << start->f << endl;

    for (State* s : allStates) delete s;
    return 0;
}
```
## Output
<img width="277" height="45" alt="Screenshot 2025-09-20 at 11 20 04 AM" src="https://github.com/user-attachments/assets/c7181d5e-a1a8-4118-96be-9f3bbf7a7bdb" />

