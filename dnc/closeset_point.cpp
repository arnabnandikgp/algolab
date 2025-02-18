#include <iostream>
#include <cmath>
using namespace std;

#define INF 1e9 // A large number to represent infinity

// Function to compute Euclidean distance
double distance(int p1[2], int p2[2]) {
    return sqrt((p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]));
}

void merge(int a[][2], int size_a, int b[][2], int size_b, int ans[][2]) {
    int i = 0, j = 0, k = 0;

    while (i < size_a && j < size_b) {
        if (a[i][0] < b[j][0]) {
            ans[k][0] = a[i][0];
            ans[k][1] = a[i][1];
            k++;
            i++;
        } else {
            ans[k][0] = b[j][0];
            ans[k][1] = b[j][1];
            k++;
            j++;
        }
    }

    while (i < size_a) {
        ans[k][0] = a[i][0];
        ans[k][1] = a[i][1];
        k++;
        i++;
    }

    while (j < size_b) {
        ans[k][0] = b[j][0];
        ans[k][1] = b[j][1];
        k++;
        j++;
    }
}

void sortByX(int arr[][2], int n) {
    if (n <= 1) {
        return;
    }

    int mid = n / 2;
    int left[mid][2];
    int right[n - mid][2];

    // Split the array into two halves
    for (int i = 0; i < mid; i++) {
        left[i][0] = arr[i][0];
        left[i][1] = arr[i][1];
    }
    for (int i = mid; i < n; i++) {
        right[i - mid][0] = arr[i][0];
        right[i - mid][1] = arr[i][1];
    }

    // Recursively sort both halves
    sortByX(left, mid);
    sortByX(right, n - mid);

    // Merge the sorted halves
    merge(left, mid, right, n - mid, arr);
}

// Brute force approach for small number of points (≤ 3)
double bruteForce(int points[][2], int n) {
    double minDist = INF;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = distance(points[i], points[j]);
            if (d < minDist) {
                minDist = d;
            }
        }
    }
    return minDist;
}

// Find the minimum distance across the split boundary
double stripClosest(int strip[][2], int size, double d) {
    double minDist = d;
    
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j][1] - strip[i][1]) < minDist; j++) {
            double dist = distance(strip[i], strip[j]);
            if (dist < minDist) {
                minDist = dist;
            }
        }
    }
    return minDist;
}

// Recursive function to find the closest pair distance using Divide & Conquer
double closestUtil(int points[][2], int n) {
    // Base case: use brute force if ≤ 3 points
    if (n <= 3) {
        return bruteForce(points, n);
    }

    int mid = n / 2;
    int midPointX = points[mid][0];

    // Left and Right parts
    double dLeft = closestUtil(points, mid);
    double dRight = closestUtil(points, n - mid);
    
    double d = (dLeft < dRight) ? dLeft : dRight;

    // Create a strip of points within distance d from the mid line
    int strip[n][2];
    int stripSize = 0;
    for (int i = 0; i < n; i++) {
        if (abs(points[i][0] - midPointX) < d) {
            strip[stripSize][0] = points[i][0];
            strip[stripSize][1] = points[i][1];
            stripSize++;
        }
    }

    // Find the minimum distance in the strip
    double minStrip = stripClosest(strip, stripSize, d);
    
    return (d < minStrip) ? d : minStrip;
}

// Wrapper function
double closestPair(int points[][2], int n) {
    sortByX(points, n);
    return closestUtil(points, n);
}

// Driver Code
int main() {
    cout<< "enter the number of points "<<"\n";
    int n;
    cin>>n;
    int points[n][2];
    for(int i=0;i<n;i++){
        for(int j=0;j<2;j++){
            cin>>points[i][j];
        }
    }
    double result = closestPair(points, n);
    cout << "The closest distance between two points is: " << result << "\n";
    // int points[][2] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};

    return 0;
}
