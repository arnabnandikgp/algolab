#include <iostream>
using namespace std;

bool isSafe(int** board, int N, int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1) return false;
    }

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false;
    }

    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1) return false;
    }

    return true;
}

bool solveNQueens(int** board, int N, int row) {
    if (row == N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << (board[i][j] ? "Q " : ". ");
            }
            cout << endl;
        }
        cout << endl;
        return true; // Return true to find one solution; modify for multiple solutions
    } 

    bool foundSolution = false;

    for (int col = 0; col < N; col++) {
        if (isSafe(board, N, row, col)) {
            board[row][col] = 1; // Place the queen
            // if (solveNQueens(board, N, row + 1)) return true;
            foundSolution = solveNQueens(board, N, row + 1) || foundSolution;

            board[row][col] = 0; // Backtrack
        }
    }

    return foundSolution;
    // return false;
}

int main() {
    int N;
    cout << "Enter the size of the board (N): ";
    cin >> N;

    int** board = new int*[N];
    for (int i = 0; i < N; i++)
    {
        board[i] = new int[N];
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            board[i][j] = 0;
        }
    }

    if (!solveNQueens(board, N, 0)) {
        cout << "No solution exists for N = " << N << "." << endl;
    }

    return 0;
}
