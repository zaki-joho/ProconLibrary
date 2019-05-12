#include "../../bits/stdc++.h"
#include "../../Structure/union_find.hpp"
#include "../graph.hpp"

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381544

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
