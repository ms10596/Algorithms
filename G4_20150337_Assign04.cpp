// GROUP:   4
// ID:      20150337
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Mohamed Sayed Mohamed
//Online Judge ID:	788797
#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;
unsigned long long cnt = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
long long CountInvMerge(long long *a, int n)
{

    int ptr = 0, lPtr = 0, rPtr = 0;
    int lN = n/2;
    long long lHalf[lN];
    for (int i = 0; i < lN; ++i) {
        lHalf[i] = a[ptr++];
    }
    int rN = n - lN;
    long long rHalf[rN];
    for (int i = 0; i < rN; ++i) {
        rHalf[i] = a[ptr++];

    }
    ptr = 0;
    while (ptr < n) {
        if (rPtr >= rN)a[ptr++] = lHalf[lPtr++];
        else if (lPtr >= lN)a[ptr++] = rHalf[rPtr++];
        else if (lHalf[lPtr] <= rHalf[rPtr]) {
            a[ptr++] = lHalf[lPtr++];
        }
        else {
            a[ptr++] = rHalf[rPtr++];
            cnt += lN - lPtr;
        }
    }
    return cnt;
}
long long CountInv(long long *a, int n)
{
    if(n == 1){
        return cnt;
    }
    long long *lHalf = a;
    int lN = n / 2;

    long long *rHalf = a + lN;
    int rN = n - lN;

    CountInv(lHalf, lN);
    CountInv(rHalf, rN);

    CountInvMerge(a, n);

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    //freopen("input.in", "r",stdin);
    int n;
    while (cin >> n) {
        if (n == 0) break;
        long long numbers[n];
        for (int i = 0; i < n; ++i) {
            cin >> numbers[i];
        }
        cout <<CountInv(numbers,n)<<endl;
        cnt = 0;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
