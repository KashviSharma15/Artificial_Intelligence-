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
