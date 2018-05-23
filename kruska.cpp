// GROUP:   4
// ID:      20150337
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Mohamed Sayed Mohamed
//Online Judge ID:	788797

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n)
    {
        n = _n;
        parent = new int[n];
        num_nodes = new int[n];
        for (int i=0; i<n; i++){
            parent[i] = i;
            num_nodes[i] = 1;
        }
    }
    void Destroy()
    {
        delete [] parent;
        delete [] num_nodes;
    }
    int Find(int i)
    {
        if(i>=0 && i<n){
            return parent[i];
        }
        throw new exception();
    }
    bool Union(int i, int j)
    {
        if(Find(i) == Find(j)){
            return false;
        }
        int initialParentOfI = Find(i);
        int cntOfParentOfI = num_nodes[initialParentOfI];
        int initialParentOfJ = Find(j);
        int cntOfParentOfJ = num_nodes[initialParentOfJ];
        for (int k=0; k<n; k++){
            if (initialParentOfI == parent[k]){
                parent[k] = initialParentOfJ;
                num_nodes[k] += cntOfParentOfJ;
            }
            else if(initialParentOfJ == parent[k]){
                num_nodes[k] += cntOfParentOfI;
            }
        }
        return true;

    }
};


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

struct Edge
{
	int u, v;
	int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input.in","r",stdin);
    unsigned long long current = 0,total = 0;
    int nodes, roads;
    while(cin>>nodes>>roads){
        if(nodes == 0 && roads == 0)break;
        Edge graph[roads];
        for (int i = 0; i < roads; ++i) {
            cin >> graph[i].u >> graph[i].v >> graph[i].w;
        }
        MergeSort(graph,roads,IsBeforeEdge);
        DisjointSets disjointSets;
        disjointSets.Initialize(nodes);
        for (int j = 0; j < roads; ++j) {
            if(disjointSets.Union(graph[j].u, graph[j].v)){
                current += graph[j].w;
            }
            total += graph[j].w;
        }
        cout << total - current <<endl;
        total = 0;
        current = 0;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////