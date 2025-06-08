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

// 0/1 Knapsack (DP)
int knapsack01(const vector<Item>& items, int capacity, vector<int>& selectedItems) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight <= w)
                dp[i][w] = max(
                    dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value
                );
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Trace selected items
    int w = capacity;
    for (int i = n; i > 0 && dp[i][w] > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selectedItems.push_back(items[i - 1].index);
            w -= items[i - 1].weight;
        }
    }

    return dp[n][capacity];
}

// Fractional Knapsack (Greedy)
double knapsackFractional(vector<Item> items, int capacity, vector<FractionalItem>& selectedItems) {
    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return (double)a.value / a.weight > (double)b.value / b.weight;
    });

    double totalValue = 0.0;
    for (const auto& item : items) {
        if (capacity >= item.weight) {
            capacity -= item.weight;
            totalValue += item.value;
            selectedItems.push_back({item.index, 1.0});
        } else {
            double frac = (double)capacity / item.weight;
            totalValue += item.value * frac;
            selectedItems.push_back({item.index, frac});
            break;
        }
    }
    return totalValue;
}

void solve01(const vector<Item>& items, int capacity) {
    vector<int> selectedItems;
    int maxValue = knapsack01(items, capacity, selectedItems);
    cout << "\n 0/1 Knapsack Result:\n";
    cout << "Total value: " << maxValue << "\n";
    cout << "Selected items (Index | Value | Weight):\n";
    for (int idx : selectedItems) {
        cout << setw(6) << idx
             << setw(8) << items[idx].value
             << setw(8) << items[idx].weight << "\n";
    }
}

void solveFractional(const vector<Item>& items, int capacity) {
    vector<FractionalItem> selectedItems;
    double maxValue = knapsackFractional(items, capacity, selectedItems);
    cout << fixed << setprecision(2);
    cout << "\n Fractional Knapsack Result:\n";
    cout << "Total value: " << maxValue << "\n";
    cout << "Selected items (Index | Value | Weight | Fraction Taken):\n";
    for (const auto& fi : selectedItems) {
        int idx = fi.index;
        cout << setw(6) << idx
             << setw(8) << items[idx].value
             << setw(8) << items[idx].weight
             << setw(10) << fi.fraction << "\n";
    }
}

int main () {
    cout << "=====  Knapsack Resource Allocation Tool =====\n";
    int n = getValidInt("Enter number of items: ", 1);

    vector<Item> items(n);
    for (int i = 0; i < n; ++i) {
        items[i].index = i;
        items[i].value = getValidInt("Item " + to_string(i + 1) + " - Value: ", 0);
        items[i].weight = getValidInt("Item " + to_string(i + 1) + " - Weight: ", 1);
    }

    int capacity = getValidInt("Enter maximum capacity of knapsack: ", 1);

    int methodChoice;
    bool solved01 = false, solvedFractional = false;

    while (true) {
        cout << "\nChoose solving method:\n";
        cout << "1. 0/1 Knapsack\n";
        cout << "2. Fractional Knapsack\n";
        methodChoice = getValidInt("Enter choice (1 or 2): ");

        if (methodChoice == 1) {
            solve01(items, capacity);
            solved01 = true;
        } else if (methodChoice == 2) {
            solveFractional(items, capacity);
            solvedFractional = true;
        } else {
            cout << "Invalid method. Please choose 1 or 2.\n";
            continue;
        }


        while (true) {
            cout << "\nDo you want to solve the problem with the ";
            if (methodChoice == 1 && !solvedFractional)
                cout << "Fractional Knapsack method?\n";
            else if (methodChoice == 2 && !solved01)
                cout << "0/1 Knapsack method?\n";
            else {
                cout << "other method again? (Already solved both)\n";
                break;
            }

            cout << "1. Yes\n2. No (Exit)\n";
            int nextChoice = getValidInt("Enter choice (1 or 2): ");
            if (nextChoice == 1) {
                if (methodChoice == 1 && !solvedFractional) {
                    solveFractional(items, capacity);
                    solvedFractional = true;
                } else if (methodChoice == 2 && !solved01) {
                    solve01(items, capacity);
                    solved01 = true;
                }
                break;
            } else if (nextChoice == 2) {
                cout << "Exiting program. Thank you!\n";
                return 0;
            } else {
                cout << "Invalid input. Try again.\n";
            }
        }

        break;
    }

    return 0;
}