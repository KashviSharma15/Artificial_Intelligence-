
## <u>AIM</u>
To solve the 8 Puzzle Problem using **Depth First Search (DFS)** 

---

## Algorithm

1. **State Structure**
   - Maintain a `state` structure with:
     - `id` → unique identifier of the state
     - `parent_id` → id of the state from which this was generated
     - `s[3][3]` → 3×3 integer array for puzzle configuration

2. **Goal Test**
   - Function `goal_test()` checks if the current state matches the goal state.

3. **Move Generation**
   - Function `generate_moves()` finds the position of the blank (0) tile.
   - Based on the blank tile’s position, generate all possible valid moves:
     - Move **Up** 
     - Move **Down** 
     - Move **Left** 
     - Move **Right** 
   - For example:
     - If blank is at `(0,0)`, moves: Right, Down
     - If blank is at `(1,1)`, moves: Up, Down, Left, Right

4. **DFS Search**
   - Use a **stack** to store states to explore.
   - Push the initial state onto the stack, mark it visited.
   - Maintain a **closed list** to store visited states.
   - While the stack is not empty:
     1. Pop the top state.
     2. If it is the goal state → reconstruct and print the path using `parent_id`.
     3. Otherwise:
        - Generate possible moves from this state.
        - For each new state:
          - If it is **not in closed list**, assign a new `id` and set its `parent_id` to the current state’s `id`, then push it to the stack.

5. **Path Reconstruction**
   - Once the goal state is found, use `parent_id` links to trace back to the initial state.
   - Print the sequence of states.

---

## Time Complexity
- **Worst-case time complexity**:  
  \[
  O(branching factor^maximum depth)
  \]  
 
- **Space complexity**:  
  DFS uses \( O(bm) \) for the stack plus space for the closed list.

---

## Use Cases
- Understanding DFS traversal in a finite state problem.
- State representation and path reconstruction.

## Code 

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct state {
    int id;
    int parent_id;
    int s[3][3];
};

bool goal_test(state current, state goal) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (current.s[i][j] != goal.s[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool visited(vector<state> closed, state cur) {
    for (int idx = 0; idx < (int)closed.size(); idx++) {
        if (goal_test(closed[idx], cur)) {
            return true;
        }
    }
    return false;
}

vector<state> generate_moves(state current, int &id_counter) {
    vector<state> moves;
    int blank_i = -1;
    int blank_j = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (current.s[i][j] == 0) {
                blank_i = i;
                blank_j = j;
            }
        }
    }

    int dir_i[4] = {-1, 1, 0, 0};
    int dir_j[4] = {0, 0, -1, 1};

    for (int k = 0; k < 4; k++) {
        int new_i = blank_i + dir_i[k];
        int new_j = blank_j + dir_j[k];

        if (new_i >= 0 && new_i < 3 && new_j >= 0 && new_j < 3) {
            state next;
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    next.s[x][y] = current.s[x][y];
                }
            }
            next.id = id_counter++;
            next.parent_id = current.id;
            int temp = next.s[blank_i][blank_j];
            next.s[blank_i][blank_j] = next.s[new_i][new_j];
            next.s[new_i][new_j] = temp;
            moves.push_back(next);
        }
    }

    return moves;
}
int main() {
    state initial;
    state goal;
    int id_counter = 1;

    cout << "Please enter the initial state (use 0 for blank):\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> initial.s[i][j];
        }
    }
    initial.id = id_counter++;
    initial.parent_id = -1;

    cout << "Please enter the goal state (use 0 for blank):\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> goal.s[i][j];
        }
    }

    if (goal_test(initial, goal)) {
        cout << "Puzzle already solved.\n";
        return 0;
    }

    stack<state> st;
    vector<state> closed;

    st.push(initial);
    closed.push_back(initial);

    bool found = false;
    state found_goal;

    while (!st.empty()) {
        state current = st.top();
        st.pop();

        if (goal_test(current, goal)) {
            found = true;
            found_goal = current;
            break;
        }

        vector<state> children = generate_moves(current, id_counter);

        for (int i = 0; i < (int)children.size(); i++) {
            if (!visited(closed, children[i])) {
                st.push(children[i]);
                closed.push_back(children[i]);
            }
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

    cout << "Puzzle Solved.\n";
    cout << "Path is :\n";
    for (int p = (int)path.size() - 1; p >= 0; p--) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cout << path[p].s[i][j] << ' ';
            }
            cout << '\n';
        }
        cout << "->\n";
    } } else {
    cout << "No solution found.\n";
}}


