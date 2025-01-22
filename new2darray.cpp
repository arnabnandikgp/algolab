#include<iostream>
using namespace std;

int main() {
    int n, m;
    cin>>n>>m;
    //dynamically allocate 2d array
    int** arr = new int*[n];
    for(int i=0;i<n;i++){
        arr[i] = new int[m];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>arr[i][j];
        }
    }
    // do your operations here

    for(int i=0;i<n;i++){
        delete[] arr[i];
    }
    delete[] arr;
    return 0;

    // statically allocate 2d array
    int arr[n][m];
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>arr[i][j];
        }
    }
    // do stuff here
    
}