#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include<cmath>
#include<cstdlib>
#include<algorithm>
#include<string>
using namespace std;
class Point{
public:
    int x, y;
};
Point closestPair[2];//for storing closest pair
//sort X coordinate
bool sortX(const Point& p1, const Point& p2){
    return p1.x < p2.x;
}
//sort y coordinate
bool sortY(const Point& p1, const Point& p2){
    return p1.y < p2.y;
}
//calculate the distance between two points
float distancee(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

//brute force to return the smallest distance between two points
float bruteForce(Point P[], int n){
    float minD = INT_MAX;
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            if (distancee(P[i], P[j]) < minD){
                minD = distancee(P[i], P[j]);
                closestPair[0]=P[i];
                closestPair[1]=P[j];
            }
        }
    }
    return minD;
}
// A utility function to find the minimum of two float values
float min(float x, float y){
    return (x < y) ? x : y;
}
//find the distance between the closest points in a strip
float stripClosest(Point strip[], int size, float d){
    float minD=d; //initialize the minimum distance as d
    sort(strip, strip + size, sortY); //sort by Y-coordinate

    for(int i = 0; i < size; ++i){
        for(int j = i + 1; j < size && (strip[j].y - strip[i].y) < minD; ++j){
            if(distancee(strip[i], strip[j]) < minD){
                minD = distancee(strip[i], strip[j]);
                closestPair[0]=strip[i];
                closestPair[1]=strip[j];
            }
        }
    }
    return minD;
}
//recursive function to find the smallest distance
float closestDtil(Point P[], int n) {
    if (n <= 3) {//BASE CASE
        return bruteForce(P, n);
    }
    int mid = n / 2;
    Point midPoint=P[mid];
//LEFT DISTANCE CALCULATE
    float dl=closestDtil(P, mid);
    float dr=closestDtil(P + mid, n - mid);//RIGHT DISTANCE CALCULATE
    float d=min(dl, dr);
    Point strip[n];
    int j = 0;
    //strip point distance calculate
    for(int i = 0; i < n; i++){
        if(abs(P[i].x - midPoint.x) < d){
            strip[j] = P[i];
            j++;
        }
    }
    return min(d, stripClosest(strip, j, d));
}

//closest point find
float closest(Point P[], int n){
    sort(P, P + n, sortX);
    return closestDtil(P, n);
}
// function to generate filenames
string filename(int k){
    stringstream fileName;
    fileName<<"file"<<k<<".txt";
    return fileName.str();
}

int main(){
    ofstream fout;
    srand(time(0));
    double x,y;
    for(int k=0;k<10;k++){
    string file =filename(k);
    fout.open(file.c_str());
    if(!fout){
        cout<<"Failed to open file.\n";
        return 1;
    }
    
    int n=rand()%150+101;
   for(int i=0;i<n;i++){
       float x = rand() % 1000 + 0.0;
        float y = rand() % 1000 + 0.0;
      fout << x << " " << y << endl; 
    }
    fout.close();}
    //DISPLAY FILES NAMES
    string fileName;
    int count=0;
    while(count!=10){
    cout<<"Enter file name from below listed Files.\n";
    for(int i=0;i<10;i++){
     cout<<i+1<<". file"<<i<<".txt"<<endl;
    }
    while(true){
        cin>>fileName;
        ifstream file(fileName.c_str());
        if(file){
            file.close();
            break;
        } else {
            cout << "File \"" << fileName << "\" does not exist. Please try again: ";
        }
    }
    ifstream file(fileName.c_str());
    int i=0;
     Point P[1000];
    while (file >> P[i].x >> P[i].y) {
        i++;
    }
    file.close();

    cout << "The smallest distance is: " << closest(P, i) << endl;
    cout << "The closest pair of points is: (" << closestPair[0].x << ", " << closestPair[0].y << ") and ("
         << closestPair[1].x << ", " << closestPair[1].y << ")" << endl;
		 count++;}

    return 0;
}
