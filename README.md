# Knapsack Resource Allocation

## Overview

This C++ program implements two classic knapsack problem-solving algorithms:
  **0/1 Knapsack** - Uses dynamic programming to solve the discrete item selection problem
  **Fractional Knapsack** - Uses a greedy algorithm to solve the continuous item selection problem
The tool allows users to input items with names, values, and weights, then select which algorithm to apply to maximize the value within a given capacity constraint.

## Data Structures

`Item` **Struct**

Represents an item that can be placed in the knapsack:

  `name`: String label for the item
  `value`: Integer value of the item
  `weight`: Integer weight of the item
  `index`: Original position in the input array (for tracking)

`FractionalItem` **Struct**

Used for fractional knapsack results:

  `index`: Original item index
  `fraction`: Fraction of the item taken (0.0 to 1.0)

## Core Functions

### Input Validation

  `getValidInt(prompt, minVal)`:

    + Ensures valid integer input ≥ minVal
    + Handles invalid input with error messages and retries

## Knapsack Algorithms

1. 0/1 Knapsack (`knapsack01`):
    + Uses dynamic programming with a 2D table
    + Returns maximum value and tracks selected items via indices
    + Time complexity: O(nW) where n=number of items, W=capacity
2. Fractional Knapsack (`knapsackFractional`):
    + Uses greedy approach based on value-to-weight ratio
    + Returns maximum value and tracks fractions taken
    + Time complexity: O(n log n) due to sorting

## Solution Display Functions

  + `solve01()`: Displays 0/1 knapsack results in formatted table
  + `solveFractional()`: Displays fractional knapsack results with fractions

## User Interface Flow

  1. Input Phase:
      + Get number of items (≥1)
      + For each item: collect name, value (≥0), and weight (≥1)
      + Get knapsack capacity (≥1)
  2. Solving Phase:
      + User selects solving method (0/1 or Fractional)
      + Program displays results
      + Option to solve with the other method or exit
  3. Output:
      + Clear tabular display of:
          - Selected item indices
          - Item names
          - Values and weights
          - Fractions taken (for fractional solution)

# Usage Example

------------------------------------------------------
===== Knapsack Resource Allocation Tool =====
Enter number of items: 3
Item 1 - Name: Gold
Item 1 - Value: 60
Item 1 - Weight: 10
Item 2 - Name: Silver
Item 2 - Value: 100
Item 2 - Weight: 20
Item 3 - Name: Bronze
Item 3 - Value: 120
Item 3 - Weight: 30
Enter maximum capacity of knapsack: 50

Choose solving method:
1. 0/1 Knapsack
2. Fractional Knapsack
Enter choice (1 or 2): 1

0/1 Knapsack Result:
Total value: 220
Selected items (Index | Name | Value | Weight):
     0      Gold      60      10
     2    Bronze     120      30
--------------------------------------------------------

## Key Features
    + Robust input validation
    + Clear, formatted output
    + Tracks original item indices and names
    + Handles both discrete and fractional selection
    + User-friendly menu system
    + Memory-efficient DP implementation for 0/1 knapsack

---------------------------------------------------------
                      # Group Members

## Name               ## GitHub username    Id no.
1. Tewodros Besha      Tew-odros            NSR/921/15
2. Desta Shewa         DestaShewa           NSR/T/016/15
3. Kidus Petros        Kidus96              NSR/570/15
4. Habtamu Abera       Juniour12            NSR/448/15
5. Tesfayesus Arza     Tesfawyesus          NSR/915/15
6. Yemisrach Tamrat    Yemi-2015            NSR/990/15  
