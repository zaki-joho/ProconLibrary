#include "../bits/stdc++.h"
#include "../Structure/union_find.hpp"

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381541
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381544

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

// プリム法による最小全域木
// 到達可能な頂点への辺の内, コストが最小のものを選んでいく
// O(ElogV)
int prim(const Graph &g)
{
    int sz = g.size();
    int ret = 0;
    std::vector<bool> used(sz, false);
    std::priority_queue<P, std::vector<P>, std::greater<P>> que;
    que.push(P(0, 0));
    while (!que.empty())
    {
        P p = que.top();
        que.pop();
        if (used[p.second])
            continue;
        used[p.second] = true;
        ret += p.first;
        for (const auto &e : g[p.second])
        {
            que.push(P(e.cost, e.to));
        }
    }
    return ret;
}

// クラスカル法による最小全域木
// 辺を重みが小さい順に閉路を作らないように追加していく
// O(ElogV), V := 頂点数
int kruskal(const Edges &es, int V)
{
    UnionFind uf(V);
    int ret = 0;
    sort(es.rbegin(), es.rend());
    for (const auto &e : es)
    {
        if (!uf.find(e.from, e.to))
        {
            ret += e.cost;
            uf.unite(e.from, e.to);
        }
    }
    return ret;
}
