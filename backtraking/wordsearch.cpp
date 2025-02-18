#include <iostream>
#include <string>
using namespace std;

bool isSafe(int** visited, int x, int y, int rows, int cols) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && visited[x][y] == 0);
}

bool searchWord(char** board, int rows, int cols, string word, int** visited, int x, int y, int index) {
    if (index == word.length())
        return true;

    if (!isSafe(visited, x, y, rows, cols) || board[x][y] != word[index])
        return false;

    visited[x][y] = 1;

    int rowOffsets[] = {-1, 1, 0, 0};
    int colOffsets[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newX = x + rowOffsets[i];
        int newY = y + colOffsets[i];
        if (searchWord(board, rows, cols, word, visited, newX, newY, index + 1))
            return true;
    }

    visited[x][y] = 0; // Backtrack
    return false;
}

bool wordSearch(char** board, int rows, int cols, string word) {
    int** visited = new int*[rows];
    for (int i = 0; i < rows; i++)
        visited[i] = new int[cols];

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            visited[i][j]=0;
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (board[i][j] == word[0] && searchWord(board, rows, cols, word, visited, i, j, 0)) {
                for (int i = 0; i < rows; i++)
                    delete[] visited[i];
                delete[] visited;
                return true;
            }
        }
    }

    for (int i = 0; i < rows; i++)
        delete[] visited[i];
    delete[] visited;

    return false;
}

int main() {
    int rows = 3, cols = 4;
    char** board = new char*[rows];
    for (int i = 0; i < rows; i++)
        board[i] = new char[cols];

    char input[3][4] = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}
    };

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            board[i][j] = input[i][j];

    string word = "ABCCED";

    if (wordSearch(board, rows, cols, word))
        cout << "Word found!" << endl;
    else
        cout << "Word not found!" << endl;

    for (int i = 0; i < rows; i++)
        delete[] board[i];
    delete[] board;

    return 0;
}
