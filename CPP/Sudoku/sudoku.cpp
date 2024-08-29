#include <iostream>
#include <vector>

const int SIZE = 9;

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (const auto& row : grid) {
        for (int num : row) {
            std::cout << num << ' ';
        }
        std::cout << '\n';
    }
}

// Function to check if placing num at grid[row][col] is valid
bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check row and column
    for (int i = 0; i < SIZE; ++i) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (grid[r + startRow][c + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    for (int row = 0; row < SIZE; ++row) {
        for (int col = 0; col < SIZE; ++col) {
            if (grid[row][col] == 0) { // Empty cell
                for (int num = 1; num <= SIZE; ++num) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;
                        if (solveSudoku(grid)) return true;
                        grid[row][col] = 0; // Backtrack
                    }
                }
                return false; // No number fits
            }
        }
    }
    return true; // Puzzle solved
}

int main() {
    std::vector<std::vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    std::cout << "Sudoku Puzzle:\n";
    printGrid(grid);

    if (solveSudoku(grid)) {
        std::cout << "\nSolved Sudoku:\n";
        printGrid(grid);
    } else {
        std::cout << "No solution exists\n";
    }

    return 0;
}
