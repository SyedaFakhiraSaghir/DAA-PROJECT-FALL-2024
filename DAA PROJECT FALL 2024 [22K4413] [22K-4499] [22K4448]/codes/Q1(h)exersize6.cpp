//ALGO PROJECT 22K-4413 22K-4448 22K-4499
#include <iostream>
#include <limits>
using namespace std;

// global array for node values
const int MAX_NODES = 1000; // max nodes
int values[MAX_NODES];
// get value of node v
int probe(int v) 
{
    return values[v];
}

int findlocalMin(int n) {
    // start at root
    int v = 1;
    while (true) {
        // get current node value
        int currentValue = probe(v);
        // track min neighbor
        int minNeighbor = v;
        int minValue = currentValue;
        // check left child
        int left = 2 * v;
        if (left <= n) {
            int leftValue = probe(left);
            if (leftValue < minValue) {
                minNeighbor = left;
                minValue = leftValue;
            }
        }
        // check right child
        int right = 2 * v + 1;
        if (right <= n) {
            int rightValue = probe(right);
            if (rightValue < minValue) {
                minNeighbor = right;
                minValue = rightValue;
            }
        }
        // check parent
        int parent = v / 2;
        if (parent >= 1) {
            int parentValue = probe(parent);
            if (parentValue < minValue) {
                minNeighbor = parent;
                minValue = parentValue;
            }
        }
        // if current node is local min, return it
        if (minNeighbor == v) {
            return v;
        }
        // move to min neighbor
        v = minNeighbor;
    }
}

int main() {
    // example tree in binary format
    values[1] = 20; 
	values[2] = 11; 
	values[3] = 2; 
	values[4] = 8;
    values[5] = 13; 
	values[6] = 18; 
	values[7] = 40; 
    int n = 7;  // number of nodes
    cout << "Local minimum found at node: " << findlocalMin(n) << "\nValue at local minimum node: " << probe(findlocalMin(n)) << endl;
    return 0;
}