#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

struct Item {
    int value;
    int weight;
    int index;
};

struct FractionalItem {
    int index;
    double fraction;
};

// Validated integer input
int getValidInt(const string& prompt, int minVal = 0) {
    int val;
    while (true) {
        cout << prompt;
        cin >> val;
        if (cin.fail() || val < minVal) {
            cout << " Invalid input. Please enter a valid number >= " << minVal << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return val;
        }
    }
}

int main () {

    return 0;
}