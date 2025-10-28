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
