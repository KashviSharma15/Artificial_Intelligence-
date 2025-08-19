# Artificial Intelligence 

---

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
