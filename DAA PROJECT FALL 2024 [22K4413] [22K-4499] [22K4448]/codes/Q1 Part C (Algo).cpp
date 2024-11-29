#include <iostream>
using namespace std;
int merge(int arr[], int start, int end, int mid) {
    int i = start;
    int j = mid + 1;
    int k = 0;
    int inversions = 0;
    int temp[end - start + 1];
    while (i <= mid && j <= end) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += (mid - i + 1);
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= end) {
        temp[k++] = arr[j++];
    }
    for (i = start; i <= end; i++) {
        arr[i] = temp[i - start];
    }
    return inversions;
}
int mergeSort(int arr[], int start, int end) {
    if (start >= end) {
        return 0;
    }
    int mid = (start + end) / 2;
    int inversions = 0;
    inversions += mergeSort(arr, start, mid);
    inversions += mergeSort(arr, mid + 1, end);
    inversions += merge(arr, start, end, mid);
    return inversions;
}
int main() {
    int arr[] = {8, 4, 2, 1,5,7,8,9,15,4};
    int n = sizeof(arr) / sizeof(arr[0]);
    int inversionCount = mergeSort(arr, 0, n - 1);
    cout << "Sorted Array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Number of Inversions: " << inversionCount << endl;
    return 0;
}
// Time Complexity:
// Best: O(n log n)
// Avg: O(n log n)
// Worst: O(n log n)


