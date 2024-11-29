//ALGO PROJECT 22K-4413 22K-4448 22K-4499
#include <iostream>
#include <functional>
#include <limits>
using namespace std;

int median(int n, function<int(int)> query_db1, function<int(int)> query_db2) {}

int main() {
    //sorted databases with different data values in each db
    int db1[] = {1, 3, 5, 7, 9, 11, 13, 15,17,19};
    int db2[] = {0, 2, 4, 6, 8, 10, 12, 14,16,18};
    //assuming data bases have same sizes
    int n = sizeof(db1) / sizeof(db1[0]);
    //to access k-th smallest element in each database
    function<int(int)> queryDb1 = [&](int k) -> int { return db1[k]; };
    function<int(int)> queryDb2 = [&](int k) -> int { return db2[k]; };
    cout << "median: " << median(n, queryDb1, queryDb2) << endl;
    return 0;
}

//using binary search
int median(int n, function<int(int)> query_db1, function<int(int)> query_db2) 
{
    int l_index = 0, r_index = n;
    //store values of split points
    int db1_leftval, db1_rightval, db2_leftval, db2_rightval;
    //find partition between databases
    while (l_index < r_index) 
    {
        // midpoint in first database
        int midpointDb1 = (l_index + r_index) / 2;
        // corresponding index in second database
        int midpointDb2 = n - midpointDb1;
        // largest value in the left of database 1
        if (midpointDb1 > 0) 
        {
            db1_leftval = query_db1(midpointDb1 - 1);
        } 
        else 
        {
            // min value if out of bounds
            db1_leftval = numeric_limits<int>::min();  
        }
        // smallest value in the right of database 1
        if (midpointDb1 < n) 
        {
            db1_rightval = query_db1(midpointDb1);
        } 
        else 
        {
            // max value if out of bounds
            db1_rightval = numeric_limits<int>::max();
        }
        // largest value in the left of database 2
        if (midpointDb2 > 0) 
        {
            db2_leftval = query_db2(midpointDb2 - 1);
        } 
        else 
        {
            // min value if out of bounds
            db2_leftval = numeric_limits<int>::min();
        }
        // minimum value in the right of database 2
        if (midpointDb2 < n) 
        {
            db2_rightval = query_db2(midpointDb2);
        } 
        else 
        {
            // max value if out of bounds
            db2_rightval = numeric_limits<int>::max();  
        }

        //if partition valid return max of left values else if db1_leftval > db2_rightval adjust search range to midpint of database 1 else search right
        if (db1_leftval <= db2_rightval && db2_leftval <= db1_rightval) 
        {
            return max(db1_leftval, db2_leftval);
        }
        else if (db1_leftval > db2_rightval) 
        {
            r_index = midpointDb1;
        }
        else 
        {
            l_index = midpointDb1 + 1;
        }
    }

    // converge binary search to one point
    int finaldb1_leftval, finaldb2_leftval;

    // get left value from database 1
    if (l_index > 0) 
    {
        finaldb1_leftval = query_db1(l_index - 1);
    } 
    else 
    {
        finaldb1_leftval = numeric_limits<int>::min();
    }

    // get left value from database 2
    if (n - l_index > 0) 
    {
        finaldb2_leftval = query_db2(n - l_index - 1);
    } 
    else 
    {
        finaldb2_leftval = numeric_limits<int>::min();
    }

    // return the larger of the two left values as the median
    return max(finaldb1_leftval, finaldb2_leftval);
}
