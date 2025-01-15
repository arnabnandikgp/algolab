#include <iostream>

using namespace std;

// Function to merge two sorted arrays
void merge(int* a, int size_a, int* b, int size_b, int* ans) {
    int i = 0, j = 0, k = 0;

    while (i < size_a && j < size_b) {
        if (a[i] < b[j]) {
            ans[k++] = a[i++];
        } else {
            ans[k++] = b[j++];
        }
    }

    while (i < size_a) {
        ans[k++] = a[i++];
    }

    while (j < size_b) {
        ans[k++] = b[j++];
    }
}

// Function to perform merge sort
void mergesort(int* arr, int n) {
    if (n <= 1) {
        return;
    }

    int mid = n / 2;
    int* left = new int[mid];
    int* right = new int[n - mid];

    // Split the array into two halves
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < n; i++) {
        right[i - mid] = arr[i];
    }

    // Recursively sort both halves
    mergesort(left, mid);
    mergesort(right, n - mid);

    // Merge the sorted halves
    merge(left, mid, right, n - mid, arr);

    // Free allocated memory
    delete[] left;
    delete[] right;
}

int main() {
    int n;
    cin >> n;

    // Dynamically allocate memory for the input array
    int* arr = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Perform merge sort
    mergesort(arr, n);

    // Print the sorted array
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Free allocated memory
    delete[] arr;

    return 0;
}
