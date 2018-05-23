// GROUP:   4
// ID:      20150337
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Mohamed Sayed Mohamed

#include <cstdio>
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

int main()
{
    int t,population,pairs,a,b;
    cin >> t;
    while(t--){
        cin >> population >>pairs;
        DisjointSets friends;
        int maxRelation = 1;
        friends.Initialize(population);
        while (pairs--){
            cin >> a >> b;
            friends.Union(a-1,b-1);
            maxRelation = max(maxRelation, friends.num_nodes[a-1]);
        }
        cout << maxRelation <<endl;
        friends.Destroy();
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////