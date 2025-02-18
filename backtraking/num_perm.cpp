#include <iostream>
using namespace std;

void printPermutations(int* nums, int size) {
    for (int i = 0; i < size; i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

void generatePermutations(int* nums, int start, int size) {
    if (start == size) {
        // Print the current permutation
        printPermutations(nums, size);
        return;
    }

    for (int i = start; i < size; i++) {
        // Swap the current element with the i-th element
        int temp = nums[start];
        nums[start] = nums[i];
        nums[i] = temp;

        // Recurse for the next index
        generatePermutations(nums, start + 1, size);

        // Backtrack: Undo the swap
        temp = nums[start];
        nums[start] = nums[i];
        nums[i] = temp;
    }
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    int* nums = new int[size];
    cout << "Enter " << size << " distinct integers: ";
    for (int i = 0; i < size; i++) {
        cin >> nums[i];
    }

    cout << "Permutations are:" << endl;
    generatePermutations(nums, 0, size);

    delete[] nums; // Free dynamically allocated memory
    return 0;
}
