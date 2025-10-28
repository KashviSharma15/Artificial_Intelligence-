## <u>AIM</u>  
To implement a Tic-Tac-Toe game using Approach 2.

---

## Algorithm

1. * Board Representation *
- Board stored as a 1D array of size `9`  
- `nil` → empty  
- `'X` → human  
- `'O` → computer  

---

### 2. Display Board
- Function `print-board` prints each cell  
- Uses `-` for empty cells  
- Prints newline after every 3 cells  

---

### 3. Winning Move Check (`POSSWIN`)
- Function `winner` checks all 8 possible winning lines  
- Condition:  
  ```lisp
  if (a = b = c ≠ nil)
      winner = a
  ```

---

### 4. Make a Move (`GO`)
- Function `best-move` tries each empty cell  
- Temporarily places `'O`  
- Calls `minimax` to evaluate score  
- Chooses move with maximum score  

---

### 5. Check Win Condition
- If `winner(board)` = `'X` → player wins  
- If `winner(board)` = `'O` → computer wins  

---

### 6. Check Draw
- Function `full-board-p(board)`  
  ```lisp
  (notany #'null board)
  ```
- If true and no winner → draw  

---

### 7. Helper Function (`MAKE2` / `minimax`)
- Recursive evaluation of moves  
- `'O` (maximizing) → choose max score  
- `'X` (minimizing) → choose min score  
- Scoring logic:  
  ```text
  X wins → -10 + depth
  O wins → +10 - depth
  Draw   → 0
  ```

---

### 8. Game Loop
1. Display board  
2. Human plays `'X`  
3. Check win/draw  
4. Computer plays `'O` using `best-move`  
5. Check win/draw  
6. Repeat until game ends  

---

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
- *Educational Purpose:* Helps students learn how algorithms can be applied to simple games.  
- *Game Development:* Can be used as a base for building simple AI opponents in Tic-Tac-Toe.  

---

## Code
```lisp
(defun make-board ()
  (make-array 9 :initial-element nil))

(defun print-board (board)
  (dotimes (i 9)
    (format t "~A " (or (aref board i) "-"))
    (when (= (mod (1+ i) 3) 0) (terpri))))

(defun winner (board)
  (let ((lines '((0 1 2) (3 4 5) (6 7 8)
                 (0 3 6) (1 4 7) (2 5 8)
                 (0 4 8) (2 4 6))))
    (dolist (line lines)
      (let ((a (aref board (first line)))
            (b (aref board (second line)))
            (c (aref board (third line))))
        (when (and a (equal a b) (equal b c))
          (return a))))))

(defun full-board-p (board)
  (notany #'null board))

(defun minimax (board depth maximizing)
  (let ((win (winner board)))
    (cond
      ((equal win 'X) (- 10 depth))
      ((equal win 'O) (+ depth 10))
      ((full-board-p board) 0)
      (t
       (if maximizing
           (let ((best -1000))
             (dotimes (i 9 best)
               (when (null (aref board i))
                 (setf (aref board i) 'O)
                 (setf best (max best (minimax board (1+ depth) nil)))
                 (setf (aref board i) nil))))
           (let ((best 1000))
             (dotimes (i 9 best)
               (when (null (aref board i))
                 (setf (aref board i) 'X)
                 (setf best (min best (minimax board (1+ depth) t)))
                 (setf (aref board i) nil)))))))))

(defun best-move (board)
  (let ((best -1000) (move -1))
    (dotimes (i 9 move)
      (when (null (aref board i))
        (setf (aref board i) 'O)
        (let ((score (minimax board 0 nil)))
          (when (> score best)
            (setf best score)
            (setf move i)))
        (setf (aref board i) nil)))))

(defun play ()
  (let ((board (make-board)))
    (loop
      (print-board board)
      (if (winner board)
          (progn
            (format t "~A wins!~%" (winner board))
            (return)))
      (if (full-board-p board)
          (progn (format t "Draw!~%") (return)))
      ;; User input 1-9
      (format t "Enter your move (1-9): ")
      (terpri)  ; prints a newline
      (let ((move (parse-integer (read-line) :junk-allowed t)))
        (when (and move (<= 1 move 9) (null (aref board (1- move))))
          (setf (aref board (1- move)) 'X)))
      (if (or (winner board) (full-board-p board))
          (progn
            (print-board board)
            (if (winner board)
                (format t "~A wins!~%" (winner board))
                (format t "Draw!~%"))
            (return)))
      ;; Computer move
      (let ((comp-move (best-move board)))
        (setf (aref board comp-move) 'O)))))

(play)
```
---

## Output

<img width="412" height="731" alt="Screenshot 2025-08-24 at 9 42 42 PM" src="https://github.com/user-attachments/assets/6c8e60ce-4e24-45dc-9f03-bdaac94a74bc" />
