//ALGO PROJECT 22K-4413 22K-4448 22K-4499
#include <iostream>
#include <algorithm>
//Sort lines by slope
//sweep from left to right
//maintain a set of lines that are currently visible at each x-coordinate. As we process each line:If a new line intersects the current set of visible lines, we check if it is visible at any x-coordinate. Maintain the lines in a balanced tree structure that allows efficient insertion, deletion, and querying of the uppermost line.

using namespace std;

class Line {
public:
    double slope, intercept;
    Line() : slope(0), intercept(0) {}

    //constructor with parameters
    Line(double slope, double intercept) : slope(slope), intercept(intercept) {}

    // calculate the y-coordinate of the line at a given x
    double y_at(double x) const {
        return slope * x + intercept;
    }

    // compare lines based on their slope
    bool operator<(const Line& other) const {
        return slope < other.slope;
    }
};

Line* merge_lines(const Line* left, int left_size, const Line* right, int right_size, int& size) {}
Line* find_visible_lines_rec(const Line* lines, int start, int end, int& size) {}
Line* find_visible_lines(Line* lines, int line_size, int& visible_size) {}

int main() {
    Line lines[] = {
        Line(6, 1),    // y = 6x + 1
        Line(8, 5),    // y = 8x + 5
        Line(5, -5),   // y = 5x - 5
        Line(1, 2)     // y = x + 2
    };
    int line_size = sizeof(lines) / sizeof(lines[0]);
    int visible_size = 0;
    Line* visible_lines = find_visible_lines(lines, line_size, visible_size);
    cout << "Visible lines:\n";
    for (int i = 0; i < visible_size; i++) {
        cout << "y = " << visible_lines[i].slope << "x + " << visible_lines[i].intercept << "\n";
    }
    delete[] visible_lines;
    return 0;
}


// merge two sets of visible lines, maintaining only the upper envelope
Line* merge_lines(const Line* left, int left_size, const Line* right, int right_size, int& size) {
    Line* res = new Line[left_size + right_size];
    int i = 0, j = 0, k = 0;
    // compare lines from the left and right halves, keeping the uppermost
    while (i < left_size && j < right_size) {
        if (left[i].y_at(0) > right[j].y_at(0)) {
            res[k++] = left[i++];
        } else {
            res[k++] = right[j++];
        }
    }
    // append any remaining lines from either half
    while (i < left_size) {
        res[k++] = left[i++];
    }
    while (j < right_size) {
        res[k++] = right[j++];
    }
    size = k;
    return res;
}

// recursive function to find visible lines using divide and conquer
Line* find_visible_lines_rec(const Line* lines, int start, int end, int& size) {
    // base case: if there is one line, it is visible
    if (end - start == 1) {
        size = 1;
        return new Line[1]{lines[start]};
    }
    // split the lines into two halves
    int mid = (start + end) / 2;
    int left_size = 0, right_size = 0;
    Line* left_visible = find_visible_lines_rec(lines, start, mid, left_size);
    Line* right_visible = find_visible_lines_rec(lines, mid, end, right_size);
    // merge the visible lines from the left and right halves
    Line* merged_visible_lines = merge_lines(left_visible, left_size, right_visible, right_size, size);
    delete[] left_visible;
    delete[] right_visible;
    return merged_visible_lines;
}

Line* find_visible_lines(Line* lines, int line_size, int& visible_size) {// find all visible lines in O(n log n) time
    // sort lines by their slopes
    sort(lines, lines + line_size);
    // use divide and conquer to find visible lines
    return find_visible_lines_rec(lines, 0, line_size, visible_size);
}
