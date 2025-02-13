#include <iostream>
using namespace std;

void make_cordinates(float **arr, float **qarr, float n)
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        qarr[k][0] = arr[i][0];
        qarr[k][1] = arr[i][1];
        k++;
        qarr[k][0] = arr[i][2];
        qarr[k][1] = arr[i][1];
        k++;
        qarr[k][0] = arr[i][0];
        qarr[k][1] = arr[i][3];
        k++;
        qarr[k][0] = arr[i][2];
        qarr[k][1] = arr[i][3];
        k++;
    }
}

int orientation(float p[2], float q[2], float r[2])
{
    int val = (q[1] - p[1]) * (r[0] - q[0]) - (q[0] - p[0]) * (r[1] - q[1]);
    if (val == 0)
    {
        return 0;
    }
    return val > 0 ? 1 : 2;
}

int middle_line(float **arr, float n)
{
    int minx1 = 0;
    int minx2 = 0;
    for (int i = 0; i < n; i++)
    {
        minx1 = min(minx1, int(arr[i][0]));
        minx2 = min(minx2, int(arr[i][2]));
    }
    return (minx1 + minx2) / 2;
}

int combine(float **combined, int n, float **sol)
{
    if (n < 3)
    {
        for(int i=0;i<n;i++)
        {
            sol[i][0] = combined[i][0];
            sol[i][1] = combined[i][1];
        }
        // copy all
        return n;
    }

    int resultsize = 0;
    int leftmost = 0;

    // for loop
    for (int i = 1; i < n; i++)
    {
        if (combined[i][0] < combined[leftmost][0])
        {
            leftmost = i;
        }
    }
    int p = leftmost, q;
    do
    {
        sol[resultsize][0] = combined[p][0];
        sol[resultsize][1] = combined[p][1];
        resultsize++;

        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            if (orientation(combined[p], combined[i], combined[q]) == 2)
            {
                q = i;
            }
        }

        p = q;
    } while (p != leftmost);

    return resultsize;
}

int merge(float **lsol, float **rsol, int lsize, int rsize, float **sol) // which will merge the spaces
{
    float **qlarr = new float *[2 * lsize];
    for (int i = 0; i < 2 * lsize; i++)
    {
        qlarr[i] = new float[2];
    }

    make_cordinates(lsol, qlarr, lsize);
    float **qrarr = new float *[2 * rsize];
    for (int i = 0; i < 2 * rsize; i++)
    {
        qrarr[i] = new float[2];
    }
    make_cordinates(rsol, qrarr, rsize);
    float **combined = new float *[lsize + rsize];
    for (int i = 0; i < lsize + rsize; i++)
    {
        combined[i] = new float[2];
    }
    int totalpoints = 0;
    for (int i = 0; i < lsize; i++)
    {
        combined[totalpoints][0] = qlarr[i][0];
        combined[totalpoints][1] = qlarr[i][1];
        totalpoints++;
    }
    for (int i = 0; i < rsize; i++)
    {
        combined[totalpoints][0] = qrarr[i][0];
        combined[totalpoints][1] = qrarr[i][1];
        totalpoints++;
    }
    return combine(combined, totalpoints, sol);
}


int dnq(float **arr, int n, float **sol) // where the actaul things will happen
{

    // base case is needed

    int y = middle_line(arr, n);
    // make two new arr with halves of the space
    // logic to divide?
    // any thing hhaving top right x cordinate less than y and more than ewaul to y
    int lsize = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i][2] < y)
        {
            lsize++;
        }
    }

    float **larr = new float *[lsize];
    for (int i = 0; i < lsize; i++)
    {
        larr[i] = new float[4];
    }
    int p = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i][2] < y)
        {
            larr[p++] = arr[i];
        }
    }

    int rsize = n - lsize;

    float **rarr = new float *[rsize];
    for (int i = 0; i < rsize; i++)
    {
        rarr[i] = new float[4];
    }
    int q = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i][1] >= y)
        {
            rarr[q++] = arr[i];
        }
    }

    float **lsol = new float *[2 * lsize];
    for (int i = 0; i < 2 * lsize; i++)
    {
        lsol[i] = new float[2];
    }
    float **rsol = new float *[2 * rsize];
    for (int i = 0; i < 2 * rsize; i++)
    {
        rsol[i] = new float[2];
    }

    dnq(larr, lsize, lsol);
    dnq(rarr, rsize, rsol);
    return merge(lsol, rsol, lsize, rsize, sol);
}

// function to return the ordinate of the middle line
//(x1, y1, x2, y2)

int main()
{
    int n;
    cout << "write n:";
    cin >> n;

    float **arr = new float *[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = new float[4];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cin >> arr[i][j];
        }
    }
    cout<<"meow";

    float **sol = new float *[2* n];
    for (int i = 0; i < 2 * n; i++)
    {
        sol[i] = new float[2];
    }
    for (int i = 0; i < 2 * n; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            sol[i][j] = -1;
        }
    }
    int size =dnq(arr, n, sol);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (sol[i][j] != -1)
            {
                cout << sol[i][j];
            }
        }
    }
}

