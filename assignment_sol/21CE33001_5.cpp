#include <iostream>
using namespace std;

void merge(int a[][2], int size_a, int b[][2], int size_b, int ans[][2])
{
    int i = 0, j = 0, k = 0;

    while (i < size_a && j < size_b)
    {
        if (a[i][0] < b[j][0])
        {
            ans[k][0] = a[i][0];
            ans[k][1] = a[i][1];
            k++;
            i++;
        }
        else
        {
            ans[k][0] = b[j][0];
            ans[k][1] = b[j][1];
            k++;
            j++;
        }
    }

    while (i < size_a)
    {
        ans[k][0] = a[i][0];
        ans[k][1] = a[i][1];
        k++;
        i++;
    }

    while (j < size_b)
    {
        ans[k][0] = b[j][0];
        ans[k][1] = b[j][1];
        k++;
        j++;
    }
}

void sortByX(int arr[][2], int n)
{
    if (n <= 1)
    {
        return;
    }

    int mid = n / 2;
    int left[mid][2];
    int right[n - mid][2];

    // Split the array into two halves
    for (int i = 0; i < mid; i++)
    {
        left[i][0] = arr[i][0];
        left[i][1] = arr[i][1];
    }
    for (int i = mid; i < n; i++)
    {
        right[i - mid][0] = arr[i][0];
        right[i - mid][1] = arr[i][1];
    }

    // Recursively sort both halves
    sortByX(left, mid);
    sortByX(right, n - mid);

    // Merge the sorted halves
    merge(left, mid, right, n - mid, arr);
}

int orientation(int p[2], int q[2], int r[2])
{
    int val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    if (val == 0)
        return 0;             // collinear
    return (val > 0) ? 1 : 2; // clock or counterclock wise
}

int findUnionBoundary(int points[][2], int n, int result[][2], int resultSize)
{
    if (n < 3)
    {
        // Convex hull not possible with fewer than 3 points
        for (int i = 0; i < n; i++)
        {
            result[i][0] = points[i][0];
            result[i][1] = points[i][1];
        }
        resultSize = n;
        return resultSize;
    }

    // Start from the leftmost point
    int leftmost = 0;
    for (int i = 1; i < n; i++)
    {
        if (points[i][0] < points[leftmost][0])
        {
            leftmost = i;
        }
    }

    int p = leftmost, q;
    resultSize = 0;

    // Loop to traverse the hull
    do
    {
        result[resultSize][0] = points[p][0];
        result[resultSize][1] = points[p][1]; // Add current point to result
        resultSize++;
        q = (p + 1) % n;

        for (int i = 0; i < n; i++)
        {
            // Find the most counterclockwise point
            if (orientation(points[p], points[i], points[q]) == 2)
            {
                q = i;
            }
        }

        p = q;
    } while (p != leftmost); // Loop until we come back to the starting point
    return resultSize;
}

int dnq(int points[][2], int n, int sol[][2])
{
    int mid = n / 2;
    int lpoints[mid][2];
    int rpoints[n - mid][2];

    for (int i = 0; i < mid; i++)
    {
        lpoints[i][0] = points[i][0];
        lpoints[i][1] = points[i][1];
    }

    for (int i = 0; i < n - mid; i++)
    {
        rpoints[i][0] = points[mid + i][0];
        rpoints[i][1] = points[mid + i][1];
    }

    int lsol[mid][2];
    int rsol[n - mid][2];

    dnq(lpoints, mid, lsol);
    dnq(rpoints, n - mid, rsol);

    int totalPoints = 0;
    int com[n][2];
    for (int i = 0; i < mid; i++)
    {
        com[totalPoints][0] = lpoints[i][0];
        com[totalPoints][1] = lpoints[i][1];
        totalPoints++;
    }
    for (int i = 0; i < n - mid; i++)
    {
        com[totalPoints][0] = rpoints[i][0];
        com[totalPoints][1] = rpoints[i][1];
        totalPoints++;
    }
    int resultsize;

    return findUnionBoundary(com, totalPoints, sol, resultsize);
}

void pointify(int input[][4], int n, int points[][2])
{
    for (int i = 0; i < n; i++)
    {
        points[4 * i][0] = input[i][0];
        points[4 * i][1] = input[i][1];
        points[4 * i + 1][0] = input[i][0] + input[i][2];
        points[4 * i + 1][1] = input[i][1];
        points[4 * i + 2][0] = input[i][0] + input[i][2];
        points[4 * i + 2][1] = input[i][1] + input[i][3];
        points[4 * i + 3][0] = input[i][0];
        points[4 * i + 3][1] = input[i][1] + input[i][3];
    }
}

int wrapper(int points[][2], int n, int sol[][2])
{
    sortByX(points, n);
    return dnq(points, n, sol);
}

int main()
{
    cout << "Enter the size of the array: ";
    int n;
    cin >> n;

    int input[n][4]; // left down corner and the dimensions(x, y, width, height)
    for (int i = 0; i < n; i++)
    {
        cin >> input[i][0] >> input[i][1] >> input[i][2] >> input[i][3];
    }
    int points[4 * n][2];

    pointify(input, n, points);

    int sol[4 * n][2];
    int ans = wrapper(points, 4 * n, sol);

    for(int i=0;i<ans;i++){
        cout<<sol[i][0]<<" "<<sol[i][1]<<"\n";
    }
}