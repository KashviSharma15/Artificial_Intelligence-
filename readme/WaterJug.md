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

## Code 

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int X, Y;     
int X0 = 0, Y0 = 0;  

void fillX() {
    X0 = X;
}

void fillY() {
    Y0 = Y;
}

void emptyX() {
    X0 = 0;
}

void emptyY() {
    Y0 = 0;
}

void pourXtoY() {
    int pour = min(X0, Y - Y0);
    X0 -= pour;
    Y0 += pour;
}

void pourYtoX() {
    int pour = min(Y0, X - X0);
    Y0 -= pour;
    X0 += pour;
}

bool reachedGoal(int goal) {
    return (X0 == goal || Y0 == goal);
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    cout << "Enter capacity of jug X: ";
    cin >> X;
    cout << "Enter capacity of jug Y: ";
    cin >> Y;
    cout << "Enter goal volume: ";
    int goal;
    cin >> goal;

    if (goal > max(X, Y) || goal % gcd(X, Y) != 0) {
        cout << "Goal not achievable with given jug sizes.\n";
        return 0;
    }

    X0 = 0; Y0 = 0;

    cout << "Initial state: (" << X0 << ", " << Y0 << ")\n";


    while (!reachedGoal(goal)) {
        if (X0 == 0) {
            fillX();
            cout << "Fill X: (" << X0 << ", " << Y0 << ")\n";
        } 
        else if (Y0 < Y) {
            pourXtoY();
            cout << "Pour X->Y: (" << X0 << ", " << Y0 << ")\n";
        } 
        else if (Y0 == Y) {
            emptyY();
            cout << "Empty Y: (" << X0 << ", " << Y0 << ")\n";
        }
    }

    cout << "Goal " << goal << " reached.\n";
    return 0;
}

```
---

## Output 

<img width="269" height="184" alt="Screenshot 2025-08-24 at 9 49 45 PM" src="https://github.com/user-attachments/assets/267e58fd-0009-42bc-81ee-3a8475af4bfa" />

