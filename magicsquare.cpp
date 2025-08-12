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