// GROUP:   4
// ID:      20150336
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    Mohamed Sayed Mohamed
// UVA Username: ms10596

#include <cstdio>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
    int v; // value (price) of object
    int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int
Knapsack1(int n, int w)
{
    if (n == 0 || w == 0)
        return T1[n][w] = 0;
    if (a[n].w > w)
    {
        if (T1[n][w] == -1)
            T1[n][w] = Knapsack1(n - 1, w);
        return T1[n][w];
    }
    if (T1[n][w] == -1)
        T1[n][w] = max(a[n].v + Knapsack1(n - 1, w - a[n].w), Knapsack1(n - 1, w));
    return T1[n][w];
}
int
ComputeKnapsack1(int N, int W)
{
    for (int i = 0; i < 1001; ++i)
    {
        for (int j = 0; j < 31; ++j)
        {
            T1[i][j] = -1;
        }
    }
    return Knapsack1(N, W);
}// Recursive - memoization - initialize T then call Knapsack1(N,W);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int
ComputeKnapsack2(int N, int W)
{//Accepted
    for (int i = 0; i <= W; ++i)
        T2[0][i] = 0;
    for (int i = 0; i <= N; ++i)
        T2[i][0] = 0;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= W; ++j)
        {
            if (a[i].w > j)
            {
                T2[i][j] = T2[i - 1][j];
            }
            else
            {
                if (a[i].v + T2[i - 1][j - a[i].w] > T2[i - 1][j])
                {
                    T2[i][j] = a[i].v + T2[i - 1][j - a[i].w];
                }
                else
                {
                    T2[i][j] = T2[i - 1][j];
                }
            }
        }
    }
    return T2[N][W];
}// Bottom-up, do not save space

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int
ComputeKnapsack3(int N, int W)
{//Accepted
    for (int i = 0; i <= W; ++i)
        T3[0][i] = 0;
    for (int i = 0; i < 2; i++)
        T3[i][0] = 0;
    for (int i = 1; i <= N; ++i)
    {
        int realI = i % 2;
        int realIMinusOne = (i - 1) % 2;
        for (int j = 1; j <= W; ++j)
        {
            if (a[i].w > j)
            {
                T3[realI][j] = T3[realIMinusOne][j];
            }
            else
            {
                if (a[i].v + T3[realIMinusOne][j - a[i].w] > T3[realIMinusOne][j])
                {
                    T3[realI][j] = a[i].v + T3[realIMinusOne][j - a[i].w];
                }
                else
                {
                    T3[realI][j] = T3[realIMinusOne][j];
                }
            }
        }
    }
    return max(T3[1][W], T3[0][W]);

}// Bottom-up, use two rows only

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int
ComputeKnapsack4(int N, int W)
{//Accepted
    for (int i = 0; i <= W; ++i)
        T4[i] = 0;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = W; j >= 0; --j)
        {
            if (a[i].w > j)
            {
                continue;
            }
            else
            {
                if (a[i].v + T4[j - a[i].w] > T4[j])
                {
                    T4[j] = a[i].v + T4[j - a[i].w];
                }
            }
        }
    }
    return T4[W];
}// Bottom-up, save maximum space

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
ComputeKnapsack(int N, int W) // Here we can choose the method
{

    return ComputeKnapsack1(N, W);
    //return ComputeKnapsack2(N,W);
    //return ComputeKnapsack3(N,W);
    return ComputeKnapsack4(N, W);
}

void
Compute()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, personsNumber, person, sum = 0;
        cin >> n;
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i].v >> a[i].w;
        }
        cin >> personsNumber;
        for (int i = 0; i < personsNumber; ++i)
        {
            cin >> person;
            cout << ComputeKnapsack(n, person);
            sum += ComputeKnapsack(n, person);
        }
        cout << sum << endl;
    }
}// Get input and call ComputeKnapsack() whenever needed

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int
main()
{
    //freopen("input.in", "r", stdin);

    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
