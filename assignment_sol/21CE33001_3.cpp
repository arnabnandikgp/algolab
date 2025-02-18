#include <iostream>
using namespace std;

void printboard(int **board, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (board[i][j] != -1)
            {
                if (board[i][j] / 10 == 0)
                {
                    cout << board[i][j] << "  ";
                }
                else
                {
                    cout << board[i][j] << " ";
                }
            }
            else
            {
                cout << "X" << " ";
            }
        }
        cout << "\n";
    }
}

bool isSafe(int **board, int n, int row, int col)
{

    if (row < n && col < n && row >= 0 && col >= 0 && board[row][col] == -1)
    {
        return true;
    }
    return false;
}

bool solveKnightmove(int **board, int n, int movecount, int row, int col, int lim)
{
    if (movecount == lim)
    {
        return true;
    }

    int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; i++)
    {
        int nx = row + dx[i];
        int ny = col + dy[i];
        if (isSafe(board, n, nx, ny))
        {
            board[nx][ny] = movecount;
            int prev = movecount;
            if (solveKnightmove(board, n, movecount + 1, nx, ny, lim))
            {
                return true;
            }
            board[nx][ny] = -1; // backtrack
        }
    }
    return false;
}

int main()
{
    cout << "Enter the value of n: ";
    int n;
    cin >> n;
    int **board = new int *[n];
    for (int i = 0; i < n; i++)
    {
        board[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            board[i][j] = -1;
        }
    }
    board[0][0] = 0;
    int lim = n * n;
    if (solveKnightmove(board, n, 1, 0, 0, lim))
    {
        printboard(board, n);
    }
    else
    {
        while (lim--)
        {
            if (solveKnightmove(board, n, 1, 0, 0, lim))
            {
                printboard(board, n);
                return 0;
            }
        }
    }

    return 0;
}