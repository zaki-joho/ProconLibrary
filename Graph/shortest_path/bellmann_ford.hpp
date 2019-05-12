#include "../../bits/stdc++.h"
#include "../graph.hpp"

// 単一始点最短経路 O(EV)
// 負閉路があれば true, otherwise false
bool findNegativeLoop(int n, const std::vector<Edge> es, int s, std::vector<int> &d)
{
    int m = es.size();
    std::vector<int> pre(n, -1);
    std::vector<bool> negative(n, false);
    d[s] = 0;
    for (int j = 0; j < n - 1; j++)
    {
        for (int i = 0; i < m; i++)
        {
            Edge e = es[i];
            if (d[e.from] != INF && d[e.to] > d[e.from] + e.cost)
            {
                d[e.to] = d[e.from] + e.cost;
                pre[e.to] = pre[e.from];
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        Edge e = es[i];
        if (d[e.from] != INF && d[e.from] + e.cost < d[e.to])
        {
            return true;
        }
    }
    return false;
}
