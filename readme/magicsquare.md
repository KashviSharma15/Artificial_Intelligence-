## <u>AIM</u>  
To generate a magic square of size n × n where n is an even integer (≥ 4).

---

## Algorithm

1. *Input Validation*  
   - Read integer n.  
   - If n < 4 or n is odd → print error and exit.  

2. *Initialize Square*  
   - Create a 2D vector square[n][n] initialized with 0.

3. *Case 1: Doubly Even Order (n % 4 == 0)*  
   - Fill numbers 1 to n² sequentially.  
   - For each cell (i, j):  
     - If (i % 4 == j % 4) *or* (i % 4 + j % 4 == 3), assign n*n + 1 - num.  
     - Otherwise assign num.  
   - This ensures diagonally symmetric replacements maintain the magic property.

4. *Case 2: Singly Even Order (n % 4 != 0)*  
   - Divide into 4 sub-squares of size n/2 × n/2.  
   - Generate a magic square for the n/2 sub-square using the *Siamese method* (odd-order).  
   - Place these sub-squares into the larger matrix with value shifts:  
     - Top-left → val  
     - Bottom-right → val + subSize  
     - Top-right → val + 2*subSize  
     - Bottom-left → val + 3*subSize  
   - Perform swaps between certain columns to maintain the magic property.

5. *Output*  
   - Print the generated n × n magic square.  
   - Each row should sum to the same constant, and all columns and diagonals will also sum to this constant.

---

## Time Complexity  
- Filling n × n matrix requires one pass.  
- *Time Complexity:* O(n²)  

---

## Space Complexity  
- Requires a 2D array of size n × n.  
- *Space Complexity:* O(n²)  

---

## Use Cases  
- *Mathematics:* Demonstrates number patterns and properties of magic squares.  
- *Cryptography & Puzzles:* Basis for constructing number-based puzzles and encoding schemes.  

---

## Code 
```cpp
#include <iostream>
#include <vector>
using namespace std;

void generatemagicsquare(int n){
    if(n%2==0){
        return;
    }
    vector<vector<int>>magicsquare(n,vector<int>(n,0));
    int i=0, j=n/2;

    for(int k=1;k<=n*n;k++){
        magicsquare[i][j]=k;

        int new_i=(i-1+n)%n;
        int new_j=(j+1)%n;

        if(magicsquare[new_i][new_j]!=0){
            i=(i+1)%n;
        }else{
            j=new_j;
            i=new_i;

        }
    }

    cout << "Magic square of size " << n << ":\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << magicsquare[i][j] << "     ";
        }
        cout << "\n";
}
}

int main(){
    int n;
    cout<<"Enter an odd number for MagicSquare:";
    cin>>n;

    generatemagicsquare(n);

    return 0;
}
