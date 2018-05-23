// GROUP:   4
// ID:      20150337
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    Mohamed Sayed Mohamed
// UVA Username: ms10596

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int ptr = 0, lPtr = 0, rPtr = 0;
    int lN = n / 2;
    Type lHalf[lN];
    for (int i = 0; i < lN; ++i)
    {
        lHalf[i] = a[ptr++];
    }
    int rN = n - lN;
    Type rHalf[rN];
    for (int i = 0; i < rN; ++i)
    {
        rHalf[i] = a[ptr++];

    }
    ptr = 0;
    while (ptr < n)
    {
        if (rPtr >= rN)a[ptr++] = lHalf[lPtr++];
        else if (lPtr >= lN)a[ptr++] = rHalf[rPtr++];
        else if (IsBefore(lHalf[lPtr],rHalf[rPtr]))
        {
            a[ptr++] = lHalf[lPtr++];
        }
        else
        {
            a[ptr++] = rHalf[rPtr++];
        }
    }

}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    if(n == 1)
    {
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

struct Obj
{
    int v;
    int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Obj& a, Obj& b)
{
    return (double)a.v/a.w > (double)b.v/b.w;
}// return true if unit value of a is greater than unit value of b

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int best_val; // the best total value found until now

int Bound(int i, int w)
{
    int bound = 0;

    for (i; i <= n; ++i)
    {
        if(a[i].w > w)break;
        bound += a[i].v;
        w -= a[i].w;

    }
    if(i <= n)
    {
        double temp =  (double)w/a[i].w*a[i].v;
        bound +=temp;
    }
    return bound;
}// upper bound on the total value of items [i..n-1] that can fit in w

void BackTrack(int i, int w, int cur_val)
{
    if (i > n)
    {
        best_val = max(best_val, cur_val);
        return;
    }
    if(w == 0)
    {
        best_val = max(best_val, cur_val);
        return;
    }
    if(cur_val + Bound(i, w) < best_val)
    {
        best_val = max(best_val, cur_val);
        return ;
    }
    if (a[i].w > w)
    {
        BackTrack(i+1, w, cur_val);
    }
    else
    {
        BackTrack(i+1, w-a[i].w, cur_val + a[i].v);
        BackTrack(i+1, w, cur_val);
    }


}// starting from item i, remaining weight w, cur_value of objects[0..i-1]

int ComputeKnapsack(int N, int W)
{
    //Accepted
    best_val = 0x7fffffff * -1;
    for(int i=1; i <= N; i++)BackTrack(i, W, 0);
    return best_val;

}// solve knapsack of N objects and W weight

void Compute()
{
    int t;
    cin >> t;
    while (t--)
    {
        int personsNumber, person, sum = 0;
        cin >> n;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i].v >> a[i].w;
        }
        MergeSort(a+1, n, IsBefore);
        cin >> personsNumber;
        for (int i = 0; i < personsNumber; ++i)
        {
            cin >> person;
            sum += ComputeKnapsack(n, person);
        }
        cout << sum << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign12_10130.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
