#include <iostream>
#include <math.h>
#include <climits>
using namespace std;
//calculate distance between two points
int calculateDistance(int a, int b) {
    return abs(a - b);
}
//to sort the points
void sortArray(int arr[], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
//to calculate closest pair in the given array
int closestPair(int arr[], int left, int right){
//no need to divide as there are only two elements
    if(right-left==1){
        return calculateDistance(arr[left],arr[right]);
 }
 //if there is only one element in the array
   if (left>=right){
        return -1;
    }
    //using divide and conquer approach
    int mid=left+(right-left)/2;
//find recursively the minimum distance on left and right side
    int leftDist=closestPair(arr,left,mid);
    int rightDist=closestPair(arr,mid + 1,right);
//find the minimum distance between two halves
    int d = min(leftDist, rightDist);
//check for the closest pair across the boundary
    int stripDist = 0;
    if (mid + 1<=right) {
        stripDist=min(d,calculateDistance(arr[mid], arr[mid + 1]));
    }
    //return the overall minimum distance
    return min(d, stripDist);
}
int closestPairr(int arr[], int n) {
    //first sort the array
    sortArray(arr, n);
    //function to find the closest pair
    return closestPair(arr, 0, n - 1);
}
int main() {
    int arr[] = {7, 1, 9, 3, 14};
    int n = sizeof(arr) / sizeof(arr[0]);
    int minDis = closestPairr(arr, n);
    cout << "The closest distance is: " << minDis << endl;

    return 0;
}

