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

    return 0;
}