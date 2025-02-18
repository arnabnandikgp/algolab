#include <iostream>
using namespace std;

int t1(int n) {
    if (n == 1) return 2;
    if (n == 2) return 1;
    return t1(n - 1) - 2 * t1(n - 2);
}

int t2(int n) {
    if (n == 1) return 2;
    if (n == 2) return 1;
    return t2(n - 1) - t2(n - 2);
}

int f(int n) {  // for n<6 we will have bubble sort and merger sort otherwise
    return (n * n) / 6;
}

void merge(int* ar1, int p, int* ar2, int q, int* ans) {
    int i = 0, j = 0, k = 0;
    while (i < p && j < q) {
        if (ar1[i] <= ar2[j]) {
            ans[k++] = ar1[i++];
        } else {
            ans[k++] = ar2[j++];
        }
    }
    while (i < p) {
        ans[k++] = ar1[i++];
    }
    while (j < q) {
        ans[k++] = ar2[j++];
    }
}

void merge_sort(int* arr, int n) {
    if (n <= 1) {
        return;
    }
    int p = n / 2;
    int q = n - p;
    int* ans = new int[n];
    int* ar1 = new int[p];
    int* ar2 = new int[q];
    for (int i = 0; i < p; i++) {
        ar1[i] = arr[i];
    }
    for (int i = p; i < n; i++) {
        ar2[i - p] = arr[i];
    }

    merge_sort(ar1, p);
    merge_sort(ar2, q);

    merge(ar1, p, ar2, q, ans);
    for (int i = 0; i < n; i++) {
        arr[i] = ans[i];
    }
}

void bubble_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) return;
    }
}

int main() {
    cout << "Input a value for n ";
    int n;
    cin >> n;
    int* A = new int[n];
    int* B = new int[n];
    cout << "\n";

    for (int i = 0; i < n; i++) {
        A[i] = t1(i + 1);
        B[i] = t2(i + 1);
    }
    cout << "The unsorted array A ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";
    // the f(.)-sorting algorithm
    if (n > f(n)) {
        merge_sort(A, n);
    } else {
        bubble_sort(A, n);
    }

    // ther code
    cout << "The sorted array A ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << "\n";

    cout << "The unsorted array B ";
    for (int i = 0; i < n; i++) {
        cout << B[i] << " ";
    }
    cout << "\n";

    // merger sort will have the best worst case scenario among the algorthms i.e nlog(n)
    merge_sort(B, n);

    cout << "The sorted array B ";
    for (int i = 0; i < n; i++) {
        cout << B[i] << " ";
    }
    cout << "\n";

    delete[] A;
    delete[] B;

    return 0;
}