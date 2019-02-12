#include "../bits/stdc++.h"

struct Edge
{
    int from, to, cost;
    Edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

using Edges = std::vector<Edge>;
using Graph = std::vector<Edges>;
using P = std::pair<int, int>;
constexpr int INF = 1e9;

// 逆順にしているので注意
bool operator<(const Edge &e, const Edge &f)
{
    return e.cost > f.cost;
}

// 単一始点最短経路, O(ElogV)
std::vector<int> dijkstra(const Graph &g, int s)
{
    std::vector<int> d((int)g.size(), INF);
    d[s] = 0;
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    que.push(P(0, s)); // P(dis, pos)
    while (!que.empty())
    {
        int dist = que.top().first;
        int v = que.top().second;
        que.pop();
        if (d[v] < dist)
            continue;
        for (const auto &e : g[v])
        {
            if (d[e.to] <= d[v] + e.cost)
                continue;
            d[e.to] = d[v] + e.cost;
            que.push(P(d[e.to], e.to));
        }
    }
    return d;
}

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

// 単一始点最短経路 最悪O(EV) だが bellmann-ford より速い
// O(E) になったりならなかったりする. 負閉路もok
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3380678
std::vector<int> spfa(const Graph &g, int s)
{
    int n = g.size();
    std::vector<int> d(n, INF);
    std::vector<int> in_q(n, 0), count(n, 0);
    std::queue<int> que;
    d[s] = 0;
    que.push(s);
    in_q[s] = 1;
    count[s]++;
    while (!que.empty())
    {
        int v = que.front();
        que.pop();
        in_q[v] = 0;
        for (const auto &e : g[v])
        {
            if (d[v] != INF && d[e.to] > d[v] + e.cost)
            {
                d[e.to] = d[v] + e.cost;
                if (!in_q[e.to])
                {
                    que.push(e.to);
                    in_q[e.to] = 1;
                    if (++count[e.to] >= n)
                    {
                        return std::vector<int>();
                    }
                }
            }
        }
    }
    return d;
}
