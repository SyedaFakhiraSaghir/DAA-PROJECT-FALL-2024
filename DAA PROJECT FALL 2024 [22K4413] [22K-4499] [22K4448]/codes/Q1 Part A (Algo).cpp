 #include <iostream>
using namespace std;
void LargestAndSmallest(int A[], int low, int high, int &largest, int &smallest) {
    if (low == high) {
        largest = A[low];
        smallest = A[low];
        return;
    }
    else if (high == low + 1) {
        if (A[low] > A[high]) {
            largest = A[low];
            smallest = A[high];
        } else {
            largest = A[high];
            smallest = A[low];
        }
        return;
    }
    else {
        int mid = (low + high) / 2;
        int largest1, smallest1, largest2, smallest2;
        LargestAndSmallest(A, low, mid, largest1, smallest1);
        LargestAndSmallest(A, mid + 1, high, largest2, smallest2);
        largest = max(largest1, largest2);
        smallest = min(smallest1, smallest2);
    }
}
int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    int A[n];
    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    int largest, smallest;
    LargestAndSmallest(A, 0, n - 1, largest, smallest);
    cout << "Largest element: " << largest << endl;
    cout << "Smallest element: " << smallest << endl;
    return 0;
}
Time Complexity 0(N)

