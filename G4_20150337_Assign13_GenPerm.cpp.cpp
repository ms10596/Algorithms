// GROUP:   4
// ID:      20150337
// Assign:  13
// Assign:  GenPerm
// UVA:     216
// Name:    Mohamed Sayed Mohamed
// UVA Username: ms10596

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>      // use built-in sqrt()
#include <iostream>
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_COMPUTERS 8

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
    int x, y;
};

double Dist(Point &a, Point &b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int n; // number of computers (input)
Point com[MAX_COMPUTERS]; // locations of computers (input)
double dist[MAX_COMPUTERS][MAX_COMPUTERS]; // dist[i][j]=distance from com[i] to com[j] (pre-computed)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

double best_val; // best value until now
int best_sol[MAX_COMPUTERS]; // best solution until now (a permutation)

int s[MAX_COMPUTERS]; // s is current permutation. s[i]=index of the ith computer in this permutation.

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void UpdateSol()
{
    double sum = 0;
    for (int i = 0; i < n - 1; ++i)
    {
        int first = s[i];
        int second = s[i + 1];
        sum += dist[first][second];
    }
    if (sum < best_val)
    {
        best_val = sum;
        for (int i = 0; i < n; ++i)
        {
            best_sol[i] = s[i];
        }
    }

}// evaluate the permutation s, then update best_val and best_sol if necessary

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Backtrack0(int i)//Accepted
{

    if (i == n)
    {
        UpdateSol();
        return;
    }
    for (int j = i; j < n; ++j)
    {
        swap(s[i], s[j]);
        Backtrack0(i + 1);
        swap(s[i], s[j]);
    }

}// backtrack using swaps
void Compute0()
{
    for (int i = 0; i < n; ++i)
    {
        s[i] = i;
    }
    Backtrack0(0);

}// do necessay initializations and call Backtrack0()

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool v[MAX_COMPUTERS]; // v[i]=true if com[i] already taken in the permutation
void Backtrack1(int i)//Accepted
{
    if (i == n)
    {
        UpdateSol();
        return;
    }
    for (int j = 0; j < n; ++j)
    {
        if(v[j] == true)
        {
            continue;
        }
        s[i] = j;
        v[j] = true;
        Backtrack1(i+1);
        v[j] = false;
    }


}// backtrack using the v[] array
void Compute1()
{
    for (int i = 0; i < n; ++i)
    {
        v[i] = false;
    }
    Backtrack1(0);

}// do necessay initializations and call Backtrack1()

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dancing Links:

int F[MAX_COMPUTERS + 1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_COMPUTERS + 1]; // B[0]=n, B[1]=0
void Remove(int i)
{
    F[B[i]] = F[i];
    B[F[i]] = B[i];
}

void Restore(int i)
{
    B[F[i]] = i;
    F[B[i]] = i;
}

void InitDancingLinks(int n)
{
    int i;
    for (i = 0; i < n; i++) F[i] = i + 1;
    F[n] = 0;
    for (i = n; i > 0; i--) B[i] = i - 1;
    B[0] = n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack2(int i)
{
    if (i == n)
    {
        UpdateSol();
        return;
    }

}// backtrack using dancing links
void Compute2()
{
    InitDancingLinks(n);
    Backtrack2(0);

}// do necessay initializations and call Backtrack2()

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComputeCore()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            dist[i][j] = Dist(com[i], com[j]);

        }

    }
    best_val = 0x7fffffff;

    // do necessay initializations of dist[][] and best_val
    //Compute0();
    Compute1();
    //Compute2();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Compute()
{
    int t = 0;
    while (true)
    {
        cin >> n;
        if (n == 0)break;
        for (int i = 0; i < n; ++i)
        {
            cin >> com[i].x >> com[i].y;
        }
        ComputeCore();
        cout << "**********************************************************" << endl;
        cout << "Network #" << ++t << endl;
        for (int i = 0; i < n - 1; ++i)
        {
            cout << "Cable requirement to connect (" << com[best_sol[i]].x << "," << com[best_sol[i]].y << ") to (" <<
                 com[best_sol[i + 1]].x << "," << com[best_sol[i + 1]].y << ") is " << fixed << setprecision(2)
                 << dist[best_sol[i]][best_sol[i + 1]] + 16 << " feet." << endl;
        }
        cout << "Number of feet of cable required is " << fixed << setprecision(2) << best_val + 16 * (n - 1) << "."
             << endl;

    }
}// get input and then call ComputeCore(); then print output

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    freopen("input_assign13_00216.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
