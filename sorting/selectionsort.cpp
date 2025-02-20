#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int *arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 0; i < n; i++)
    {
        int cur_min = i;
        for (int j = i; j < n; j++)
        {
            if (arr[cur_min] > arr[j])
            {
                cur_min = j;
            }
        }
        swap(arr[i], arr[cur_min]);
    }

    for(int i=0;i<n;i++)
    {
        cout<<arr[i];
    }
}
