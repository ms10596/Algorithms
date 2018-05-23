// GROUP:   4
// ID:      20150337
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Mohamed Sayed Mohamed
//Online Judge ID:	788797

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int n, sz;
    Value *arr;

    void Initialize()
    {
        this->n = 1;
        this->sz = 0;
        this->arr = new Value[this->n];
    }

    void Destroy()
    {
        delete[] arr;
        sz = 0;
        n = 0;
    }

    void AddLast(Value v)
    {
        if (sz < n) {
            arr[sz++] = v;
        } else {
            n *= 2;
            Value *newArr = new Value[n];
            for (int i = 0; i < sz; i++)newArr[i] = arr[i];
            newArr[sz++] = v;
            delete[] arr;
            arr = newArr;
        }
    }

    void RemoveLast()
    {
        if (sz < 1) {
            throw new exception;
        }
        if (sz < n / 2) {
            n /= 2;
            Value *newArr = new Value[n];
            for (int i = 0; i < sz; i++)newArr[i] = arr[i];
            delete [] arr;
            arr = newArr;
        } else --sz;
    }

    Value &operator[](int i)
    {
        return arr[i];
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
    Array<int> adj;

    void Initialize()
    {
        adj.Initialize();
    }
    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n)
    {
        n = _n;
        nodes = new Node[n];
        for (int i=0; i<n; i++)
        {
            nodes[i].Initialize();
        }
    }
    void Destroy()
    {
        for (int i=0; i<n; i++)
        {
            nodes[i].Destroy();
        }
        delete [] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int size = 5000;
template <class Type>
struct Queue
{
    int f, n;
    Type* elems;

    void Initialize(int size)
    {
        n = 0;
        f = 0;
        elems = new Type[size];
        memset(elems,-1,size*sizeof(Type));
    }
    void Destroy()
    {
        delete [] elems;
    }
    void Add(Type t)
    {
        if(elems[n] == -1){
            elems[n] = t;
            n = (n+1)%size;
        }
        else {
            throw new exception();
        }

    }
    Type Pop()
    {
        if(elems[f] != -1){
            Type first = elems[f];
            elems[f] = -1;
            f = (f+1)%size;
            return first;
        }
        else{
            throw new exception();
        }
    }
    Type Peek()
    {
        if(elems[f] == -1){
            throw new exception();
        }
        return elems[f];
    }
    int Num()
    {
        if(n == f)return 0;
        else if(n > f)return n - f;
        else return size - f + n;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    cin >> size;
    Graph graph;
    graph.Initialize(size);
    for (int i=0; i<size; i++)
    {
        int friendsNum;
        cin >>friendsNum;
        while (friendsNum--)
        {
            int aFriend;
            cin >> aFriend;
            //cout << aFriend <<" ";
            graph.nodes[i].adj.AddLast(aFriend);
        }
    }

    int t;
    cin>>t;
    while(t--)
    {
        Queue<int> breadth;
        breadth.Initialize(size);
        int maxReach = 0,maxReachDay = 1,daysCnt=0;
        int employee;
        cin >> employee;
        bool* vis=new bool[size];
        memset(vis, 0, ((sizeof(bool))*size));
        vis[employee]=1;
        breadth.Add(employee);
        while(breadth.Num())
        {
            int currentSize = breadth.Num();
            while(currentSize--){
                int cur=breadth.Pop();
                for(int i=0;i<graph.nodes[cur].adj.sz;i++)
                {
                    int x=graph.nodes[cur].adj[i];
                    if(!vis[x])
                    {
                        vis[x]=1;
                        breadth.Add(x);
                    }
                }

            }
            ++daysCnt;
            currentSize = breadth.Num();
            if (currentSize > maxReach)
            {
                maxReach = currentSize;
                maxReachDay = daysCnt;
            }


        }
        if (maxReach == 0){
            cout << 0 <<endl;
        }
        else cout <<maxReach << " " << maxReachDay <<endl;
        breadth.Destroy();
    }
    graph.Destroy();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
