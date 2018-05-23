// GROUP:   4
// ID:      20150336
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    Mohamed Sayed Mohamed
// UVA Username: ms10596

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b)
{
    if(a == b)
    {
        return T[a][b] == 0;
    }
    if(T[a][b]>-1)
    {
        return T[a][b];
    }
    for (int k = a+1; k <= b; k++)
    {
        int newValue = MatChain(a, k-1) + MatChain(k,b) + p[a] * p[b+1] * p[k];
        if(T[a][b] == -1)
        {
            T[a][b] = newValue;
            D[a][b] = k;
        }
        else if(newValue < T[a][b])
        {
            T[a][b] = newValue;
            D[a][b] = k;
        }
    }
    return T[a][b];

}// Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
void MatChainTopDown(int n)
{
    for (int i = 0; i <n ; ++i)
    {
        for (int j = 0; j <n; ++j)
        {
            T[i][j] = -1;
        }
    }
    MatChain(0, n-1);

}// Initialize T then call MatChain(0,n)

// BottomUp version
void MatChainBottomUp(int n)
{
    for (int i = 0; i <n ; ++i)
    {
        for (int j = 0; j <n; ++j)
        {
            T[i][j] = 0x7FFFFFFF;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            int row = j, col = j + i;
            if(col >= n)continue;
            if(row == col)
            {
                T[row][col] = 0;
                continue;
            }

            for (int k = row+1; k <= col; k++)
            {
                int intial = T[row][col];
                int first = T[row][k-1];
                int second = T[k][col];
                int newValue = first + second + p[row]*p[col+1]*p[k];
                if(newValue < intial)
                {
                    T[row][col] = newValue;
                    D[row][col] = k;
                }
            }
        }
    }
}


// Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
    if(b == a)
    {
        cout << "A"<<a+1;
        return;
    }
    cout << "(";
    MatChainSol(a,D[a][b]-1);
    cout << " x ";
    MatChainSol(D[a][b], b);
    cout << ")";
}

void Compute()
{
    int t=0;
    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
            break;
        int i,l,w;
        for (i = 0; i < n; ++i)
        {
            cin >> l >> w;
            p[i] = l;
        }
        p[n] = w;
        MatChainBottomUp(n);//Accepted
        //MatChainTopDown(n);//Accepted
        cout << "Case " <<++t<<": ";
        MatChainSol(0, n-1);
        cout << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign10_00348.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
