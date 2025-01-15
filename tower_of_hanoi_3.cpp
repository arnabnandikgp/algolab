#include <iostream>
#include <cstdlib>

using namespace std;

void towerofhanoi(int n, char from_rod, char to_rod, char aux_rod) {

    if(n==0) {
        return;
    }
    towerofhanoi(n-1, from_rod, aux_rod, to_rod);
    cout<< "transfer disk "<< n << " from tower " << from_rod << " to rod "<< to_rod<<"\n";
    towerofhanoi(n-1, aux_rod, to_rod, from_rod);
}
int main() {
    int n;
    cin>>n;
    towerofhanoi(n, 'A', 'B', 'C');
    return 0;
}