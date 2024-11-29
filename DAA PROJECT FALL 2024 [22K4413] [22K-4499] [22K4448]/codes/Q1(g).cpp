//ALGO PROJECT 22K-4413 22K-4448 22K-4499
#include <iostream>
#include <climits>
using namespace std;

//max money to be found using divide and conquer
void maximum_money(int p[],int left, int right);
void find(int p[],int left, int mid, int right);

int maximum = 0;
int buy_index = 0;
int sell_index = 0;

//main for input and function calls
int main() {
    int n;
    cout<<"Enter number of consecutive days : ";
    cin>> n;
    int p[n];
    for(int i=0;i<n;i++)
    {
        cout<<"Enter stock price on day"<<i+1<<": ";
        cin>> p[i];
    }
    maximum_money(p,0,n-1);
    cout<<"buy on : "<< buy_index+1<<"\nsell on : "<<sell_index+1;
    return 0;
}

//allows partitioning 
void maximum_money(int p[],int left, int right)
{
    if (left >= right)
        return;
//determine mid point
    int mid = left + (right - left) / 2;
    maximum_money(p, left, mid);
    maximum_money(p, mid + 1, right);
    find(p, left, mid, right);
}

void find(int p[],int left, int mid, int right)
{
	//finding the min in left half and max in right half 
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int highL=0,highR=0;
    int lowL=INT_MAX,lowR=INT_MAX;
    int index_HL, index_HR;
    int index_LL, index_LR;
    int L[n1],R[n2];
    
    //find min
    for (int i = left; i <= mid; i++) 
    {
        if (p[i] < lowL) {
            lowL = p[i];
            index_LL = i;
        }
    }
//find max
    for (int j = mid + 1; j <= right; j++) 
    {
        if (p[j] > highR) {
            highR = p[j];
            index_HR = j;
        }
    }
//commpare profits
    int current_profit = highR - lowL;
    if (current_profit > maximum) 
    {
        maximum = current_profit;
        buy_index = index_LL;
        sell_index = index_HR;
    }

}
