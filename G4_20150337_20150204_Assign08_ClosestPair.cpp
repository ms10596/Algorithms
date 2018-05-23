// GROUP:   4
// ID:      20150337
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name1:   Mohamed Sayed Mohamed
// Name2:   Mohamed Ashraf Refaie
// UVA Username: ms10596/788797

#include <cstdio>
#include <iomanip>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
#include <cfloat>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int ptr = 0, lPtr = 0, rPtr = 0;
    int lN = n / 2;
    Type lHalf[lN];
    for (int i = 0; i < lN; ++i) {
        lHalf[i] = a[ptr++];
    }
    int rN = n - lN;
    Type rHalf[rN];
    for (int i = 0; i < rN; ++i) {
        rHalf[i] = a[ptr++];

    }
    ptr = 0;
    while (ptr < n) {
        if (rPtr >= rN)a[ptr++] = lHalf[lPtr++];
        else if (lPtr >= lN)a[ptr++] = rHalf[rPtr++];
        else if (IsBefore(lHalf[lPtr],rHalf[rPtr])) {
            a[ptr++] = lHalf[lPtr++];
        }
        else {
            a[ptr++] = rHalf[rPtr++];
        }
    }

}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if(n == 1){
        return ;
    }
    Type *lHalf = a;
    int lN = n / 2;

    Type *rHalf = a + lN;
    int rN = n - lN;

    MergeSort(lHalf, lN, IsBefore);
    MergeSort(rHalf, rN, IsBefore);

    Merge(a, n, IsBefore);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
    double x,y;
};
bool IsBeforeY(Point& a, Point& b)
{
    return a.y < b.y;
}
bool IsBeforeX(Point& a, Point& b)
{
    return a.x < b.x;
}

double dist(Point& a, Point& b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{
    if(n <= 3){
        double mini = DBL_MAX;
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j <n ; ++j) {
                if(dist(p[i], p[j]) < mini){
                    mini = dist(p[i], p[j]);
                }
            }
        }
        MergeSort(p, n, IsBeforeY);
        return mini;
    }
    int mid= n /2;
    double xMid = 0.5 * (p[mid-1].x + p[mid].x);
    double smallestLeft = ClosestPair(p, mid);
    double smallestRight = ClosestPair(p + mid , n - mid );
    double smallest = min(smallestLeft, smallestRight);
    MergeSort(p, n, IsBeforeY);
    Point* strip = new Point[n];
    int stripN=0;
    for (int i = 0; i < n; ++i) {
        if(abs(p[i].x - xMid ) <= smallest){
            strip[stripN++] = p[i];
        }
    }
    double smallestRes = DBL_MAX;
    for (int i = 0; i < stripN; ++i) {
        for (int j = i + 1; j < stripN &&(strip[j].y - strip[i].y)<smallestRes; ++j) {
            if(dist(strip[i], strip[j]) < smallestRes){
                smallestRes = dist(strip[i], strip[j]);
            }
        }
    }
    delete[] strip;
    return min(smallest, smallestRes);

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input.in", "r", stdin);
    int n;
    while(cin >> n){
        if(n == 0) break;
        Point* p = new Point[n];

        for (int i = 0; i < n; ++i) {
            cin >> p[i].x >> p[i].y;
        }
        MergeSort(p, n, &IsBeforeX);
        double smallest = ClosestPair(p, n);
        if (smallest < 10000)
        {
            cout << fixed << setprecision(4) << smallest << endl;
        }
        else
        {
            cout << "INFINITY" << endl;
        }
        delete[] p;
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////