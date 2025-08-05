#include <iostream>
using namespace std;

class state {
public:
    int id;
    int parent_id;
    int s[3][3];
};

bool goal_test(const state &obj) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (obj.s[i][j] == obj.goal[i][j] )
                return true;
        }
    }
    return false;
}

generate_moves(const state &obj){
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (obj.s[i][j] == "-" ){
                
            }
        }
    }
}

int main() {
    state initial;
    state goal;

    cout << "Please enter the current state:\n";
    cout << " If it is black enter - \n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> initial.s[i][j];
        }
    }
    initial.id = 1,
    initial.parent_id = 0;

    cout << "Please enter the goal state:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> goal.s[i][j];
        }
    }

    if (goal_test(obj)) {
        cout << "Goal state reached!\n";
    } else {
        generate_moves(obj);
    }

    return 0;
}



