// GROUP:   4
// ID:      20150334
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Mohamed Sayed Mohamed
// Username: ms10596

#include <cstdio>
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
        if (sz < n)
        {
            arr[sz++] = v;
        }
        else
        {
            n *= 2;
            Value *newArr = new Value[n];
            for (int i = 0; i < sz; i++)newArr[i] = arr[i];
            newArr[sz++] = v;
            arr = newArr;
        }
    }

    void RemoveLast()
    {
        if (sz < 1)
        {
            throw new exception;
        }
        --sz;
    }

    Value &operator[](int i)
    {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
    Array<Elem> a;

    bool (*IsBefore)(int &, int &);

    void Initialize(bool (*_IsBefore)(int &, int &))
    {
        a.Initialize();
        a.AddLast(-1);
        this->IsBefore = _IsBefore;
    }

    void Destroy()
    {
        a.Destroy();
    }

    int Child(int i)
    {
        return i * 2;
    }

    int Parent(int i)
    {
        return i / 2;
    }

    void MoveUp(int ind)
    {
        while (IsBefore(a[ind], a[Parent(ind)]) && ind > 1)
        {
            swap(a[ind], a[Parent(ind)]);
            ind = Parent(ind);
        }

    }

    void MoveDown(int ind)
    {
        int left = 0, right = 0;
        while (ind < a.sz)
        {
            left = Child(ind);
            right = Child(ind) + 1;
            if (left >= a.sz && right >= a.sz) return;
            if (right >= a.sz && IsBefore(a[left], a[ind]))
            {
                swap(a[left], a[ind]);
                ind = left;
            }
            else if (IsBefore(a[left], a[ind]) && IsBefore(a[left], a[right]) && right < a.sz)
            {
                swap(a[left], a[ind]);
                ind = left;
            }
            else if (IsBefore(a[right], a[ind]) && IsBefore(a[right], a[ind]) && right < a.sz)
            {
                swap(a[right], a[ind]);
                ind = right;
            }
            else return;
        }
    }

    void Add(Elem e)
    {
        a.AddLast(e);
        MoveUp(a.sz - 1);
    }

    Elem GetFirst()
    {
        return a[1];
    }

    Elem RetrieveFirst()
    {
        Elem temp = a[1];
        a[1] = a[a.sz - 1];
        a[a.sz - 1] = temp;
        a.RemoveLast();
        MoveDown(1);
        return temp;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int &a, int &b)
{
    return a < b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    long long sum = 0;
    bool (*fun)(int &, int &);
    fun = &IsBeforeInt;
    int n, number;

    while (cin >> n)
    {
        if (n == 0) break;
        Heap<int> heap;
        heap.Initialize(fun);
        for (int i = 0; i < n; i++)
        {
            cin >> number;
            heap.Add(number);
        }
        while (heap.a.sz > 2)
        {
            int first = heap.RetrieveFirst();
            int second = heap.RetrieveFirst();
            first += second;
            heap.Add(first);
            sum += first;
        }
        cout << sum << endl;
        sum = 0;

    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
