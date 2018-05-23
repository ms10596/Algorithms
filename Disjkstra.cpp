// GROUP:   X
// ID:      XXXXXXXX
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   XX FIRST STUDENT FULL NAME
// Name2:   XX SECOND STUDENT FULL NAME
// UVA Username: UVA username of student

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array {
    int n, sz;
    Value *arr;

    void Initialize() {
        this->n = 1;
        this->sz = 0;
        this->arr = new Value[this->n];
    }

    void Destroy() {
        delete[] arr;
        sz = 0;
        n = 0;
    }

    void AddLast(Value v) {
        if (sz < n) {
            arr[sz++] = v;
        } else {
            n *= 2;
            Value *newArr = new Value[n];
            for (int i = 0; i < sz; i++)newArr[i] = arr[i];
            newArr[sz++] = v;
            arr = newArr;
        }
    }

    void RemoveLast() {
        if (sz < 1) {
            throw new exception;
        }
        --sz;
    }

    Value &operator[](int i) {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap {
    int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n){
        a.Initialize();
        Elem elem;
        a.AddLast(elem);
        this->IsBefore = _IsBefore;
        pos = new int[n];
        memset(pos, -1, n);
    } // n is required to allocate and initialize pos[]
    void Destroy(){
        a.Destroy();
        delete[] pos;
    }
    void Print(){
        for (int i = 0; i < a.sz; ++i) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    int Child(int i){
        return i * 2;

    }
    int Parent(int i){
        return i/2;
    }
    Elem GetFirst(){
        return a[1];

    }
    Elem RetrieveFirst(){
        Elem temp = a[1];
        pos[a[1].v] = -1;
        a[1] = a[a.sz - 1];
        a[a.sz - 1] = temp;
        a.RemoveLast();
        MoveDown(1);
        return temp;
    }
    void Add(Elem e){
        a.AddLast(e);
        pos[e.v] = a.sz -1;
        MoveUp(a.sz - 1);
    }
    void MoveUp(int ind){
        while (IsBefore(a[ind], a[Parent(ind)]) && ind > 1) {
            swap(a[ind], a[Parent(ind)]);
            swap(pos[a[ind].v], pos[Parent(ind)]);
            ind = Parent(ind);
        }
    }
    void MoveDown(int ind){

    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int		v;
    int		w;
};

struct Node
{
    Array<Edge> adj;

    void Initialize()
    {
        adj.Initialize();
    }
    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph {
    int n;
    Node *nodes;

    void Initialize(int _n) {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; ++i) {
            nodes[i].Initialize();
        }
    }

    void Destroy() {
        for (int i = 0; i < n; ++i) {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
    return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    freopen("input.in", "r", stdin);
    int N,cases=0;
    cin >> N;
    while(N--){
        int n,m,S,T;
        long long totalCost = 0;
        cin >> n >> m >> S >> T;

        Graph graph;
        graph.Initialize(n);

        Heap <Edge> edges;
        edges.Initialize(&IsBefore);

        bool acquired[n], reachable = true;
        memset(acquired,0,n);
        acquired[S] = 1;
        if(m == 0){
            cout << "Case #" << ++cases <<": unreachable"<<endl;
            continue;
        }

        for (int i = 0; i < m; ++i) {
            int source, destination, time;
            cin >> source >> destination >> time;
            Edge edge;
            edge.v = destination;
            edge.w = time;
            graph.nodes[source].adj.AddLast(edge);

            Edge otherEdge;
            otherEdge.v = source;
            otherEdge.w = time;
            graph.nodes[destination].adj.AddLast(otherEdge);
        }
        //print(graph);

        for (int i = 0; i < graph.nodes[S].adj.sz; ++i) {

            edges.Add(graph.nodes[S].adj[i]);
        }
        //cout <<edges.a.sz;

        while(!acquired[T] && edges.a.sz > 0){
            Edge next = edges.RetrieveFirst();
            while(acquired[next.v]  && edges.a.sz > 0){
                next = edges.RetrieveFirst();
            }
            if(edges.a.sz == 0 && acquired[next.v]){
                reachable = false;
                break;
            }
            for (int i = 0; i < graph.nodes[next.v].adj.sz; ++i) {
                if(graph.nodes[next.v].adj[i].v != next.v){
                    edges.Add(graph.nodes[next.v].adj[i]);
                }
            }
            acquired[next.v] = 1;
            totalCost += next.w;

        }
        if(reachable)cout << "Case #" << ++cases <<": "<<totalCost<<endl;
        else cout << "Case #" << ++cases <<": unreachable"<<endl;
        edges.Destroy();
        graph.Destroy();
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////