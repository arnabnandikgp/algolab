#include <iostream>

using namespace std;
// pivot based
int partition(int *arr, int low, int high)
{                          // the real code
    int pivot = arr[high]; // Choose the last element as the pivot
    int i = low - 1;       // Pointer for the smaller element

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1; // Return the pivot index
}

void quicksort(int *arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high); // the index of our pivot

        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    quicksort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    delete[] arr;

    return 0;
}
