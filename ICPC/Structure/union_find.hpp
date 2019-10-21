#include "../bits/stdc++.h"

class UnionFind
{
    std::vector<int> data;
    int root_count; // 集合の個数

public:
    UnionFind(int size) : data(size, -1), root_count(size) {}
    bool unite(int x, int y)
    {
        x = root(x);
        y = root(y);
        if (x != y)
        {
            if (data[y] < data[x])
                std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
            root_count--;
        }
        return x != y;
    }
    bool find(int x, int y)
    {
        return root(x) == root(y);
    }
    int root(int x)
    {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }
    int size(int x)
    {
        return -data[root(x)];
    }
    int count() const
    {
        return root_count;
    }
};
