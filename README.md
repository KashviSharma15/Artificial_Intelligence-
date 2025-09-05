# Artificial_Intelligence
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

## <u>AIM</u>
To solve the 8 Puzzle Problem using **Breadth First Search (BFS)**

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

4. **BFS Search**
   - Use a **queue** to store states to explore.
   - Enqueue the initial state and mark it visited.
   - Maintain a **closed list** to store visited states.
   - While the queue is not empty:
     1. Dequeue the front state.
     2. If it is the goal state → reconstruct and print the path using `parent_id`.
     3. Otherwise:
        - Generate possible moves from this state.
        - For each new state:
          - If it is **not in closed list**, assign a new `id` and set its `parent_id` to the current state’s `id`, then enqueue it.

5. **Path Reconstruction**
   - Once the goal state is found, use `parent_id` links to trace back to the initial state.
   - Print the sequence of states.

---

## Time Complexity
- **Worst-case time complexity**:  
  \[
  O(branching factor^depth of the shallowest goal node.)
  \]  
- **Space complexity**:  
  BFS uses \(O(b^d)\) due to storing all generated nodes in the queue and closed list.

---

## Use Cases
- Finding the shortest path in terms of number of moves.
- Demonstrating level-order traversal in a finite state problem.

---

## <u>AIM</u>  
To solve the 8 Puzzle Problem using a **heuristic search** approach based on the number of misplaced tiles.

---

## Algorithm

1. **State Structure**  
   - Maintain a `state` structure with:  
     - `id` → unique identifier of the state  
     - `parent_id` → id of the state from which this was generated  
     - `s[3][3]` → 3×3 integer array representing the puzzle configuration  

2. **Goal Test**  
   - Function `goal_test()` checks if the current state matches the goal state.

3. **Heuristic Function**  
   - Function `heuristic_value()` calculates the number of misplaced tiles compared to the goal configuration (excluding the blank tile).  
   - This heuristic guides the search towards states that are closer to the goal.

4. **Move Generation**  
   - Function `generate_moves()` identifies the position of the blank tile (0).  
   - Generates all possible valid moves by sliding tiles **Up**, **Down**, **Left**, or **Right** into the blank space, depending on the blank tile’s position.

5. **Heuristic Search (Best-First Search)**  
   - Maintain a **priority queue (min-heap)** that stores states keyed by their heuristic value.  
   - Initialize the heap with the initial state and an empty closed list for visited states.  
   - While the heap is not empty:  
     1. Extract the state with the minimum heuristic value.  
     2. If this state matches the goal → stop and reconstruct the path.  
     3. Otherwise, generate successor states.  
     4. For each successor state not already visited:  
        - Assign a new `id` and set its `parent_id` to the current state’s `id`.  
        - Push it into the heap and add to the closed list.

6. **Path Reconstruction**  
   - Once the goal state is found, use `parent_id` links to backtrack from the goal state to the initial state.  
   - Print the sequence of states showing the steps to solve the puzzle.

---

## Time Complexity  
- The worst-case complexity depends on the branching factor and maximum search depth.  
- Heuristic search prunes the search space, generally performing better than uninformed search.

---
## <u>AIM</u>  
To solve the 8-puzzle problem using the **Hill Climbing** heuristic search algorithm with Manhattan distance.

---

## Algorithm

1. **State Representation**  
   - Represent the puzzle board as a 3×3 matrix.  
   - Track the position of the empty tile (0) as `(zero_row, zero_col)`.  
   - Maintain a heuristic value indicating estimated distance to goal.

2. **Heuristic Calculation**  
   - Use the **Manhattan distance** heuristic: sum of distances of each tile from its goal position.

3. **Neighbor Generation**  
   - Generate all possible next states by sliding a tile adjacent to the empty space into the empty space.  
   - Valid moves: up, down, left, right (if within bounds).

4. **Hill Climbing Search**  
   - Start from the initial puzzle state.  
   - At each step, compute neighbors and their heuristic values.  
   - Move to the neighbor with the lowest heuristic if it improves over the current state.  
   - Stop if no neighbor has better heuristic (local maximum) or goal is reached.

5. **Goal Test**  
   - Check if current board configuration matches the goal board.

---

## Time Complexity  
- Depends on the number of states explored before getting stuck in a local maximum or reaching goal.  
- Typically faster than exhaustive search but can get stuck prematurely.

---

## Space Complexity  
- Stores current state and neighbors, so \(O(b)\) where \(b\) is branching factor (up to 4 moves).

---

## Use Cases  
- Illustrates heuristic-based local search algorithms.  
- Useful for solving small puzzles with admissible heuristics.
  
---
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

## <u>AIM</u>  
To solve the classic Water Jug problem using a simulation approach that performs sequential operations to measure a target volume.

---

## Algorithm

1. **Initialize Jug Capacities and States**  
   - Input capacities of jug X and jug Y.  
   - Maintain current volumes `X0` and `Y0` initialized to 0.

2. **Check Feasibility**  
   - Verify that the goal volume is less than or equal to the maximum jug capacity.  
   - Verify that the goal volume is a multiple of the greatest common divisor (GCD) of X and Y.  
   - If not feasible, print an error message and exit.

3. **Operations**  
   - **Fill X**: Fill jug X to its capacity.  
   - **Fill Y**: Fill jug Y to its capacity.  
   - **Empty X**: Empty jug X completely.  
   - **Empty Y**: Empty jug Y completely.  
   - **Pour X to Y**: Pour water from jug X into jug Y until jug Y is full or jug X is empty.  
   - **Pour Y to X**: Pour water from jug Y into jug X until jug X is full or jug Y is empty.

4. **Simulation Loop**  
   - Start with both jugs empty `(X0, Y0) = (0, 0)`.  
   - Repeat until either jug contains the goal volume:  
     - If jug X is empty, fill jug X.  
     - Else if jug Y is not full, pour from X to Y.  
     - Else if jug Y is full, empty jug Y.  
   - After each operation, print the current state.

5. **Goal Test**  
   - Check if `X0 == goal` or `Y0 == goal`. If yes, the goal is reached.

---

## Time Complexity  
- Linear in the number of steps until goal is reached; bounded by jug capacities.

---

## Space Complexity  
- Constant space, tracking only current volumes and constants.

---

## Use Cases  
- Classic puzzle problem solving.  
- Demonstrates rule based approach.

---

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

---

## <u>AIM</u>
To implement a **Tic-Tac-Toe** game using the `Minimax` algorithm.

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

---

## <u>AIM</u>
To solve a graph traversal problem using the **AO\*** algorithm.  

---

## Algorithm

1. **State Structure**
   ~Each state represents a position `(x, y)` in the grid with the following attributes:~  
   - `x, y` → coordinates of the state  
   - `g` → cost from start to this node  
   - `h` → heuristic cost to goal  
   - `f` → evaluation function `f = g + h`  
   - `solved` → boolean flag if goal is reached  
   - `isAndNode` → marker for AND nodes  
   - `children` → vector of successor states  

2. **Heuristic Function**
   ~The heuristic used is Manhattan distance between the current state and the goal:~  
   \[
   h(n) = |x_{current} - x_{goal}| + |y_{current} - y_{goal}|
   \]  

3. **Successor Generation**
   ~For a given state `(x, y)`, valid successors are generated by moving in four directions (Up, Down, Left, Right), provided the new coordinates are within grid bounds.~  

4. **AO\* Search**
   - Recursively apply AO\* on child nodes.  
   - For each node:  
     - If no successors → assign large cost.  
     - Otherwise, compute the cost of the best child.  
   - Mark a state as solved if it matches the goal.  

5. **Final Evaluation**
   ~The algorithm computes the final cost from start to goal and displays it.~  

---

## Time Complexity
- **Worst-case time complexity:**  
  \[
  O(b^d)
  \]  
  ~where \(b\) = branching factor and \(d\) = depth of solution.~  

---

## Space Complexity
~AO\* requires storing explored states, hence~  
\[
O(bd)
\]  

---

## Use Cases
- Solving **AND-OR search problems** in AI.  
- Game playing strategies.  
- Planning problems where states can be decomposed into subproblems.  

---

## <u>AIM</u>
To solve a grid-based search problem using the **Alpha-Beta Pruning** algorithm.  

## Algorithm

1. **State Structure**
   ~Each state represents a position `(x, y)` in the grid with the following attributes:~  
   - `x, y` → coordinates of the state  
   - `g` → path cost from the start  
   - `h` → heuristic value (Manhattan distance to goal)  
   - `f` → evaluation function value  
   - `solved` → boolean flag if the goal is reached  
   - `isMaxNode` → indicates whether the node is a MAX or MIN player  
   - `children` → vector of successor states  

2. **Heuristic Function**
   ~The heuristic used is Manhattan distance between the current state and the goal:~  
   \[
   h(n) = |x_{current} - x_{goal}| + |y_{current} - y_{goal}|
   \]  

3. **Successor Generation**
   ~From a given state `(x, y)`, generate all valid successors by moving Up, Down, Left, or Right, ensuring the moves stay inside the grid boundaries.~  

4. **Alpha-Beta Pruning**
   - For **MAX nodes**:
     - Initialize value as \(-\infty\).  
     - Recursively evaluate children.  
     - Update `alpha = max(alpha, value)`.  
     - Prune if `beta <= alpha`.  
   - For **MIN nodes**:
     - Initialize value as \(+\infty\).  
     - Recursively evaluate children.  
     - Update `beta = min(beta, value)`.  
     - Prune if `beta <= alpha`.  
   - If the goal state is reached, mark it as solved.  

5. **Path Reconstruction**
   ~After the search, follow the best child from the start node to reconstruct the path leading to the goal.~  

## Time Complexity
- **Worst-case time complexity (without pruning):**  
  \[
  O(b^d)
  \]  
  ~where \(b\) is the branching factor and \(d\) is the maximum depth.~  

- **With Alpha-Beta Pruning (best case):**  
  \[
  O(b^{d/2})
  \]  

## Space Complexity
~The space complexity is determined by the maximum depth of the recursion stack:~  
\[
O(d)
\]  

## Use Cases
- Efficient decision-making in **two-player games** like Chess, Tic-Tac-Toe, and Checkers.  
- Search problems where pruning reduces unnecessary exploration.  
- AI applications requiring **minimax optimization with pruning**.  
