#include<iostream>
using namespace std;

void swapIfGreater(int* a, int* b, int ind1, int ind2)
{
    if(a[ind1]> b[ind2])
    {
        swap(a[ind1], b[ind2]);
    }
}
//the gap logic
void merge(int* larr, int p, int* rarr, int q, int* arr)
{
    int len = p+q;
    int gap = len/2+len%2;
    while(gap>0)
    {
        int left= 0;
        int right = left+gap;
        while(right<len)
        {   //arr1 and arr2
            if(left<p && right>=p)
            {
                swapIfGreater(larr,rarr,left,right-p);

            }
            // arr2 both
            else if(left>=p)
            {
                swapIfGreater(larr,arr,left-p,right-p);

            }
            //arr1 both
            else
            {
                swapIfGreater(arr,rarr,left,right);
            }
        }
    }
}

void merge_sort(int* arr, int n)
{
    int p = n/2;
    int q = n-p;
    int* larr = new int[p];
    int* rarr = new int[q];

    for(int i=0;i<p;i++)
    {
        larr[i]=arr[i];
    }
    for(int i=p;i<n;i++)
    {
        rarr[i-p]=arr[i];
    }

    merge_sort(larr,p);
    merge_sort(rarr,q);

    merge(larr,p,rarr,q,arr);
    
}
int main()
{
    int n;
    cin>>n;
    int* arr = new int[n];
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }

    merge_sort(arr, n);

}