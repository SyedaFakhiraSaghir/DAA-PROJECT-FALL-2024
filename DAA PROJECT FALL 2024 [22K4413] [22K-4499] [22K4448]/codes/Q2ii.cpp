//ALGO PROJECT 22K-4413 22K-4448 22K-4499
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include<math.h>
using namespace std;

// function to generate filenames
string filename(int i) {
    stringstream fileName;
    fileName << "iifile" << i + 1 << ".txt";
    return fileName.str();
}

// function to create 10 files with random numbers
int createfiles() {
    srand(time(0));
    int n = rand() % 100 + 50; // number of random integers between 50 and 150
    for (int i = 0; i < 10; i++) {
        string file = filename(i);
        ofstream out(file, ios::out);
        if (!out) {
            cout << "error opening file " << i + 1 << " for writing." << endl;
            return 0; // return 0 if file can't be created
        }
        // write n random integers to the file
        for (int j = 0; j < n; j++) {
            out << rand() % 200 + 10 << endl;
        }
        out.close();
    }
    return n; // return the number of integers generated in each file
}

// function to implement karatsuba's algorithm
long long karatsuba(long long x, long long y) {
    if (x < 10 || y < 10) { // base case: single-digit multiplication
        return x * y;
    }

    // calculate the size of the numbers
    int n = max(to_string(x).length(), to_string(y).length());
    int m = n / 2;

    // split the numbers into two halves
    long long high_x = x / (long long)pow(10, m);
    long long low_x = x % (long long)pow(10, m);
    long long high_y = y / (long long)pow(10, m);
    long long low_y = y % (long long)pow(10, m);

    // recursively compute the three products
    long long p1 = karatsuba(high_x, high_y);
    long long p2 = karatsuba(low_x, low_y);
    long long p3 = karatsuba(high_x + low_x, high_y + low_y);

    // combine the results using karatsuba's formula
    return p1 * pow(10, 2 * m) + (p3 - p1 - p2) * pow(10, m) + p2;
}

int main() {
    string file1, file2;
    int n = createfiles(); // create files and get the number of elements

    if (n == 0) {
        cout << "error: files not created properly." << endl;
        return 1;
    }

    int x[n] = {0}, y[n] = {0};
    int count1 = 0, count2 = 0;

    // display file names
    cout << "displaying file names: \n";
    for (int i = 0; i < 10; i++) {
        cout << filename(i) << " ";
    }

    // user input for file names
    cout << "\nenter file 1 to choose inputs for x: ";
    cin >> file1;
    cout << "\nenter file 2 to choose inputs for y: ";
    cin >> file2;

    // open the files for reading
    ifstream f1(file1);
    ifstream f2(file2);

    if (!f1) {
        cout << "error opening file 1!" << endl;
        return 1;
    }
    if (!f2) {
        cout << "error opening file 2!" << endl;
        return 1;
    }

    string line1, line2;

    // read lines from both files and convert them to integers
    while (getline(f1, line1) && getline(f2, line2)) {
        stringstream ss1(line1), ss2(line2);
        int num1, num2;

        // convert line 1 to an integer and store it in x
        if (ss1 >> num1) {
            x[count1++] = num1;
        } else {
            cout << "can't convert line to integer: " << line1 << endl;
        }

        // convert line 2 to an integer and store it in y
        if (ss2 >> num2) {
            y[count2++] = num2;
        } else {
            cout << "can't convert line to integer: " << line2 << endl;
        }

        // print the product of the values from both arrays using karatsuba's algorithm
        if (count1 > 0 && count2 > 0) {
            long long result = karatsuba(x[count1 - 1], y[count2 - 1]);
            cout << result << " ";
            ofstream out("OUTPUTQ2(ii)", ios::out);
		    if (!out) {
		        cout << "error opening file for writing." << endl;
		        return 0; // return 0 if file can't be created
		    }
		    out << result << " ";
		    out.close();
        }
    }
    // close the files after reading
    f1.close();
    f2.close();

    return 0;
}
