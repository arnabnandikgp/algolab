#include<iostream>

using namespace std;

// implement heapsort without using stl library

int main() {
    int n;
    cin>>n;
    int* arr = new int[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }

    // heapify the array
    for(int i=n/2-1;i>=0;i--){
        int child = i;
        while(child>0){
            int parent = (child-1)/2;
            if(arr[parent]<arr[child]){
                swap(arr[parent], arr[child]);
                child = parent;
            }
            else{
                break;
            }
        }
    }

    // sort the array
    for(int i=n-1;i>=0;i--){
        swap(arr[0], arr[i]);
        int parent = 0;
        int left = 2*parent+1;
        int right = 2*parent+2;
        while(left<i){
            int child = left;
            if(right<i && arr[right]>arr[left]){
                child = right;
            }           
            if(arr[parent]<=arr[child]){
                break;
            }
            swap(arr[parent], arr[child]);
            parent = child;
            left = 2*parent+1;
            right = 2*parent+2;
        }
    }

    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    return 0;
}