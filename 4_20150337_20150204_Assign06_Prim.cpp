// GROUP:   4
// ID:      20150337
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name1:   Mohamed Sayed Mohamed
// Name2:   Mohamed Ashraf Abdelhady
// UVA Username: ms10596

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <iomanip>

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
        /*if (sz < n / 2) {
            n /= 2;
            Value *newArr = new Value[n];
            for (int i = 0; i < sz; i++)newArr[i] = arr[i];
            arr = newArr;
        } else*/ --sz;
    }

    Value &operator[](int i) {
        return arr[i];
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge {
    int v;  // id of the adjacent node
    double w;  // edge weight = distance between the two nodes
};

struct Node {
    int x, y; // x and y coordinates of the node
    Array<Edge> adj;

    void Initialize() {
        adj.Initialize();
    }

    void Destroy() {
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

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n = 100) {
    double start = 0, end = v;
    int cnt = 0;
    while(start < end && cnt < n){
        double mid = (start + end) /2;
        if(mid * mid < v){
            start = mid;
        }
        else {
            end = mid;
        }
        ++cnt;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Elem>
struct Heap {
    Array<Elem> a;

    bool (*IsBefore)(Elem &, Elem &);

    void Initialize(bool (*_IsBefore)(Elem &, Elem &)) {
        a.Initialize();
        Elem elem;
        a.AddLast(elem);
        this->IsBefore = _IsBefore;
    }

    void Destroy() {
        a.Destroy();
    }

    int Child(int i) {
        return i * 2;
    }

    int Parent(int i) {
        return i / 2;
    }

    void MoveUp(int ind) {
        while (IsBefore(a[ind], a[Parent(ind)]) && ind > 1) {
            swap(a[ind], a[Parent(ind)]);
            ind = Parent(ind);
        }

    }

    void MoveDown(int ind) {
        int left = 0, right = 0;
        while (ind < a.sz) {
            left = Child(ind);
            right = Child(ind) + 1;
            if (left >= a.sz && right >= a.sz) return;
            if (right >= a.sz && IsBefore(a[left], a[ind])) {
                swap(a[left], a[ind]);
                ind = left;
            } else if (IsBefore(a[left], a[ind]) && IsBefore(a[left], a[right]) && right < a.sz) {
                swap(a[left], a[ind]);
                ind = left;
            } else if (IsBefore(a[right], a[ind]) && IsBefore(a[right], a[ind]) && right < a.sz) {
                swap(a[right], a[ind]);
                ind = right;
            } else return;
        }
    }

    void Add(Elem e) {
        a.AddLast(e);
        MoveUp(a.sz - 1);
    }

    Elem GetFirst() {
        return a[1];
    }

    Elem RetrieveFirst() {
        Elem temp = a[1];
        a[1] = a[a.sz - 1];
        a[a.sz - 1] = temp;
        a.RemoveLast();
        MoveDown(1);
        return temp;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(Edge &a, Edge &b) {
    return a.w < b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
double distance(int x1, int y1, int x2, int y2) {
    return Sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
    freopen("input.in", "r", stdin);
    int n, t = 0;
    while (cin >> n) {
        if (n == 0) break;
        bool reached[n]; 
        memset(reached, 0, n);
        double mx = 0;
        int cnt = 1;
        reached[0] = 1;
        Heap<Edge> edges;
        edges.Initialize(&IsBeforeInt);
        Graph stones;
        stones.Initialize(n);

        for (int i = 0; i < n; i++) { //building nodes
            int x, y;
            cin >> x >> y;
            stones.nodes[i].x = x;
            stones.nodes[i].y = y;
        }

        for (int i = 0; i < n; i++) { //building roads
            for (int j = 0; j < n; j++) {
                if (i != j) { 
                    Edge edge;
                    edge.v = j;
                    edge.w = distance(stones.nodes[i].x, stones.nodes[i].y, stones.nodes[j].x, stones.nodes[j].y);
                    stones.nodes[i].adj.AddLast(edge);
                }

            }
        }
        
        
        for (int i = 0; i < stones.nodes[0].adj.sz; ++i) { //first node is here with its neighbors
            edges.Add(stones.nodes[0].adj[i]);
        }

        while (cnt < n && !reached[1]) { //stop when meeting fiona
            Edge next = edges.RetrieveFirst(); // shortest road
            while (reached[next.v]) { // making sure that the road joining an unvisited node
                next = edges.RetrieveFirst();
            }
            for (int i = 0; i < stones.nodes[next.v].adj.sz; ++i) {//next node is here with its neighbors
                edges.Add(stones.nodes[next.v].adj[i]);
            }
            reached[next.v] = true;//visited
            mx = max(mx, next.w);
            ++cnt;

        }
        edges.Destroy();


        cout << "Scenario #" << ++t << endl;
        cout << "Frog Distance = " << fixed << setprecision(3) << mx << endl << endl;
        stones.Destroy();
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////