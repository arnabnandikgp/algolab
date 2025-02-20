#include <iostream>
using namespace std;
#define endl "\n"

void deleteRoot(int *nheap, int n)
{
    swap(nheap[n - 1], nheap[0]);
    int pindex = 0;
    int maxchild = max(nheap[2 * pindex], nheap[2 * pindex + 1]);
    int maxchild_index = maxchild == nheap[2 * pindex] ? 2 * pindex : 2 * pindex + 1;
    while (maxchild > nheap[pindex] && pindex <= n - 2)
    {

        swap(nheap[pindex], nheap[maxchild_index]);
        maxchild = max(nheap[2 * pindex], nheap[2 * pindex + 1]);
        pindex = maxchild == nheap[2 * pindex] ? 2 * pindex : 2 * pindex + 1;
    }
}
void addToHeap(int *heap, int n, int num, int *nheap)
{
    for (int i = 0; i < n; i++)
    {
        nheap[i] = heap[i];
    }
    nheap[n] = num;
    int par = n / 2;
    int child = n;
    while (par >= 0 && nheap[par] < nheap[child])
    {
        swap(nheap[par], nheap[child]);
        if (par == 0)
        {
            break;
        }
        child = par;
        par = par / 2;
    }
}

void heapify(int *arr, int n, int *heap)
{
    for (int i = 0; i < n; i++)
    {
        heap[i] = arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        int par = i / 2;
        int j = i;
        while (par >= 0)
        {
            if (heap[par] < heap[j])
            {
                swap(heap[par], heap[j]);
            }
            j = par;
            if (par == 0)
            {
                break;
            }
            par = par / 2;
        }
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
    int *heap = new int[n];
    heapify(arr, n, heap);
    for (int i = 0; i < n; i++)
    {
        cout << heap[i] << " ";
    }
    cout << "\n";
    cout << "enter the number to insert in heap" << "\n";
    int new_num;
    cin >> new_num;
    int *nheap = new int[n + 1];
    addToHeap(heap, n, new_num, nheap);
    for (int i = 0; i < n + 1; i++)
    {
        cout << nheap[i] << " ";
    }
    cout << "\n";
    // deletion we want to delete the top element and get the top element as in the last of the array
    deleteRoot(nheap, n + 1);
    deleteRoot(nheap, n);
    deleteRoot(nheap, n-1);
    deleteRoot(nheap, n-2);

    cout << "after root deletion" << "\n";
    for (int i = 0; i < n + 1; i++)
    {
        cout << nheap[i] << " ";
    }
}