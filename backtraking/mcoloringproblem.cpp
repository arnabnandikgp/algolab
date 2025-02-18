#include <iostream>
using namespace std;

bool isSafe(int **graph, int node, int color, int *colors)
{
    for (int i = 0; i < node; i++)
    {
        if (graph[node][i] == 1 && colors[i] == color)
        {
            return false;
        }
    }
    return true;
}

bool solveColoringUtil(int **graph, int N, int m, int *colors, int node)
{
    if (node == N)
    {
        return true;
    }

    // iterating over all possibilities and backtraking
    for (int c = 1; c <= m; c++)
    {
        if (isSafe(graph, node, c, colors))
        {
            colors[node] = c;
            if (solveColoringUtil(graph, N, m, colors, node + 1))
            {
                return true;
            }
            colors[node] = 0; // backtrack
        }
    }

    return false;
}

void solveColoring(int **graph, int N, int m)
{
    int *colors = new int[N];
    for (int i = 0; i < N; i++)
    {
        colors[i] = 0;
    }

    if (solveColoringUtil(graph, N, m, colors, 0))
    {
        for (int i = 0; i < N; i++)
            cout << "Node " << i << " --> Color " << colors[i] << endl;
    }
    else
    {
        cout << "No solution exists!" << endl;
    }

    delete[] colors;
}

int main()
{
    int n, m;
    cin >> n >> m;
    int **graph = new int *[n];
    for (int i = 0; i < n; i++)
    {
        graph[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> graph[i][j];
        }
    }

    solveColoring(graph, n, m);

    for (int i = 0; i < n; i++)
    {
        delete[] graph[i];
    }
    delete[] graph;
    return 0;
}