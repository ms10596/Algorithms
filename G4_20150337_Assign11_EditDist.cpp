// GROUP:   4
// ID:      20150337
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    Mohamed Sayed Mohamed
// UVA Username: ms10596

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];
int EditDist1(int n, int m)
{
    if(n == 0)
    {
        D[n][m] = 1;
        return m;
    }
    if(m == 0)
    {
        D[n][m] = 3;
        return n;
    }
    if(a[n-1] == b[m-1])
    {
        if(T1[n][m] != -1)
        {
            D[n][m] = 2;
            return T1[n][m];
        }
        return T1[n][m]=EditDist1(n-1, m-1);
    }
    int firstPath, secondPath, thirdPath;
    if(T1[n][m-1] != -1)firstPath = T1[n][m-1];
    else firstPath = EditDist1(n, m-1);
    if(T1[n-1][m] != -1)secondPath = T1[n-1][m];
    else secondPath = EditDist1(n-1, m);
    if(T1[n-1][m-1] != -1)thirdPath = T1[n-1][m-1];
    else thirdPath = EditDist1(n-1, m-1);
    return min(min(firstPath, secondPath),thirdPath)+1;
}
int ComputeEditDist1(int N, int M)
{
    for (int i = 0; i <= N ; ++i)
    {
        for (int j = 0; j <= M ; ++j)
        {
            T1[i][j] = -1;
        }
    }
    return EditDist1(N, M);
}// Recursive - memoization - initialize T then call EditDist1(N,M);

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M)//Accepted
{
    for (int i = 0; i <= M; ++i)
    {
        T2[0][i] = i;
        D[0][i] = 3;
    }
    for (int i = 0; i <= N; ++i)
    {
        T2[i][0] = i;
        D[i][0] = 1;
    }
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= M; ++j)
        {
            if(a[i-1] == b[j-1])
            {
                T2[i][j] = T2[i-1][j-1];
                D[i][j] = 2;
            }
            else
            {
                T2[i][j] = min(min(T2[i-1][j], T2[i-1][j-1]), T2[i][j-1]);
                if(T2[i][j] == T2[i-1][j])
                {
                    D[i][j] = 1;
                }
                else if(T2[i][j] == T2[i-1][j-1])
                {
                    D[i][j] = 2;
                }
                else if(T2[i][j] == T2[i][j-1])
                {
                    D[i][j] = 3;
                }
                ++T2[i][j];

            }
        }
    }
    return T2[N][M];
}// Bottom-up, do not save space

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];

int ComputeEditDist3(int N, int M)
{
    for (int i = 0; i <= M; ++i)
    {
        T3[0][i] = i;
        D[0][i] = 3;
    }
    for (int i = 0; i < 2; ++i)
    {
        T3[i][0] = i;
        D[i][0] = 1;
    }
    for (int realI = 1; realI <= N; ++realI)
    {
        int i = realI%2;
        T3[i][0] = realI;
        D[i][0] = 1;
        if(i)
        {
            for (int j = 1; j <= M; ++j)
            {
                if(a[realI-1] == b[j-1])
                {
                    T3[i][j] = T3[i-1][j-1];
                    D[i][j] = 2;
                }
                else
                {
                    T3[i][j] = min(min(T3[i-1][j], T3[i-1][j-1]), T3[i][j-1]);
                    if(T3[i][j] == T3[i-1][j])
                    {
                        D[i][j] = 1;
                    }
                    else if(T3[i][j] == T3[i-1][j-1])
                    {
                        D[i][j] = 2;
                    }
                    else if(T3[i][j] == T3[i][j-1])
                    {
                        D[i][j] = 3;
                    }
                    ++T3[i][j];
                }
            }
        }
        else
        {
            for (int j = 1; j <= M; ++j)
            {
                if(a[realI-1] == b[j-1])
                {
                    T3[i][j] = T3[i+1][j-1];
                }
                else
                {
                    T3[i][j] = min(min(T3[i+1][j], T3[i+1][j-1]), T3[i][j-1]);
                    if(T3[i][j] == T3[i+1][j])
                    {
                        D[i][j] = 1;
                    }
                    else if(T3[i][j] == T3[i+1][j-1])
                    {
                        D[i][j] = 2;
                    }
                    else if(T3[i][j] == T3[i][j-1])
                    {
                        D[i][j] = 3;
                    }
                    ++T3[i][j];
                }
            }
        }

    }
    return T3[N%2][M];
}// Bottom-up, use two rows only

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M)
{
    for (int i = 0; i <= M; ++i)
    {
        T4[i] = i;
    }
    for (int i = 1; i <= N ; ++i)
    {
        int oldValue=i-1, otherOldValue;
        T4[0]=i;
        for (int j = 1; j <= M; ++j)
        {
            if(a[i-1] == b[j-1])
            {
                otherOldValue = T4[j];
                T4[j] = oldValue;
                D[i][j] = 2;
                oldValue = otherOldValue;
            }
            else
            {
                otherOldValue = T4[j];
                T4[j] = min(min(T4[j], T4[j-1]), oldValue)+1;
                if(T4[j] == otherOldValue)
                {
                    D[i][j] = 1;
                }
                else if(T4[j] == T4[j-1])
                {
                    D[i][j] = 2;
                }
                else if(T4[j] == oldValue)
                {
                    D[i][j] = 3;
                }
                oldValue = otherOldValue;
            }
        }
    }
    return T4[M];

}// Bottom-up, save maximum space

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
    int n,m;
    int oper;
};

Oper opers[81];

int EditDistSol(int N, int M)
{
    int cnt = 0;
    while(N != 0 || M != 0)
    {
        if(D[N][M] == 1)
        {
            opers[cnt].n = N;
            opers[cnt].m = M;
            opers[cnt].oper = 1;
            --N;
            ++cnt;
        }
        else if(D[N][M] == 2)
        {
            if(a[N-1] == b[M-1])
            {
                --N;
                --M;
                continue;
            }
            opers[cnt].n = N;
            opers[cnt].m = M;
            opers[cnt].oper = 2;
            --N;
            --M;
            ++cnt;
        }
        else if(D[N][M] == 3)
        {
            opers[cnt].n = N;
            opers[cnt].m = M;
            opers[cnt].oper = 3;
            --M;
            ++cnt;
        }
    }
    int deletes = 0;
    for (int i = cnt-1; i >= 0 ; --i)
    {
        cout <<  cnt - i<< " ";
        if(opers[i].oper == 1)
        {
            cout <<"Delete "<<opers[i].n-deletes<<endl;
            ++deletes;

        }
        else if(opers[i].oper == 2)
        {
            cout << "Replace "<<opers[i].n-deletes<<","<<b[opers[i].m-1]<<endl;
        }
        else
        {
            --deletes;
            cout << "Insert "<<opers[i].n-deletes<<","<<b[opers[i].m-1]<<endl;
        }
    }

}// Print the solution using D[][]

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
    //return ComputeEditDist1(N,M);
    return ComputeEditDist2(N,M);
    //return ComputeEditDist3(N,M);
    //return ComputeEditDist4(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
    int cas=0;
    while(true)
    {
        a[0]=0;
        b[0]=0;
        if(!fgets(a,82,stdin)) break;
        fgets(b,82,stdin);
        a[strlen(a)-1]=0;
        b[strlen(b)-1]=0;
        if(cas) cout<<endl; // print an empty line between test cases
        int N=strlen(a), M=strlen(b);
        cout << ComputeEditDist(N,M) << endl;
        EditDistSol(N,M);
        cas++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign11_00526.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
