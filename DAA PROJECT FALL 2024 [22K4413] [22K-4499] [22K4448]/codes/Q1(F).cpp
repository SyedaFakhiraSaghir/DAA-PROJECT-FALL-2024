#include<iostream>
#include<limits.h>
using namespace std;
int find_peak(int A[], int left, int right){
    int mid=(left + right) / 2;
    //Handle boundaries 
    int left_value =(mid - 1 >= left) ? A[mid - 1] : INT_MIN;
    int right_value =(mid + 1 <= right) ? A[mid + 1] : INT_MIN;
    //Check if the middle element is greater than its neighbors
    if(left_value < A[mid] && A[mid] > right_value){
        return mid;  // A[mid] is a peak
    }
    //If the elements in right side of array is greater
    else if(A[mid] < right_value){
        return find_peak(A, mid + 1, right);
    }
    //If the elements in left side of array is greater
    else{
        return find_peak(A, left, mid - 1);
    }
}
int main(){
    int n;
    cout<< "Enter the size of the array (minimum 10): ";
    cin>>n;
    if(n < 10){
        cout<< "Size must be at least 10." << endl;
        return 1;
    }
    int A[n];
    cout<< "Enter " << n << " integers: ";
    for(int i = 0; i < n; i++){
        cin>>A[i];
    }
    int peak_index=find_peak(A, 0, n - 1);
    cout<<"The peak entry is A[" << peak_index << "] = "<<A[peak_index]<<endl;
    return 0;
}

