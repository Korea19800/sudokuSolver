#include <bits/stdc++.h>
using namespace std;

const int N = 9;  // Size of the Sudoku grid

void printGrid(int grid[N][N]) {
    // Print the Sudoku grid
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << grid[i][j] << " ";
        }
        cout << '\n';
    }
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check if it is safe to place the number 'num' at grid[row][col]
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) return false;  // Check row
        if (grid[i][col] == num) return false;  // Check column
        int boxRow = row - row % 3 + i / 3;
        int boxCol = col - col % 3 + i % 3;
        if (grid[boxRow][boxCol] == num) return false;  // Check 3x3 box
    }
    return true;
}

bool solveSudoku(int grid[N][N], int row, int col) {
    // Solve the Sudoku grid starting from (row, col)
    if (row == N - 1 && col == N) return true;  // Grid is solved

    if (col == N) {  // Move to the next row
        row++;
        col = 0;
    }

    if (grid[row][col] != 0) {  // Skip the filled cells
        return solveSudoku(grid, row, col + 1);
    }

    for (int num = 1; num <= 9; num++) {  // Try all possible numbers
        if (isSafe(grid, row, col, num)) {  // Check if it is safe to place num
            grid[row][col] = num;
            if (solveSudoku(grid, row, col + 1)) return true;
        }
        grid[row][col] = 0;  // Backtrack if no solution is found
    }
    return false;  // No solution found
}

int main() {
    int grid[N][N];

    // Input the Sudoku grid
    cout << "Welcome. Enter a file name\n";
  
    string fname;
    cin >> fname;
    ifstream fin;    
    string nums;  // variable to store string numbers in sudoku
    vector<int> v; // 1 dimension vector to store 81 numbers in sudoku
  
    fin.open(fname);
    // if there is no file that user entered
    if( !fin ){
        cerr << "Cannot find the file. Write the correct file name\n";
        exit(100);
    }
  
    // reading the file
    while (!fin.eof()){
      fin >> nums;
      v.push_back(stoi(nums));
    }
    fin.close();
  
    // moving numbers from 1d vector to 2d array
    for(int i = 0; i < N*N; i++){
        grid[ i / 9][ i % 9] = v[i];
    }
  
    // solving sudoku
    if (solveSudoku(grid, 0, 0)) {
        cout << "\n\nSolution:\n\n";
        printGrid(grid);
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
