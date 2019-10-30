#include "../../bits/stdc++.h"
#include "../graph.hpp"

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381541

// プリム法による最小全域木
// 到達可能な頂点への辺の内, コストが最小のものを選んでいく
// O(ElogV)
int prim(const Graph &g) {
  int sz = g.size();
  int ret = 0;
  std::vector<bool> used(sz, false);
  std::priority_queue<P, std::vector<P>, std::greater<P>> que;
  que.push(P(0, 0));
  while (!que.empty()) {
    P p = que.top();
    que.pop();
    if (used[p.second]) continue;
    used[p.second] = true;
    ret += p.first;
    for (const auto &e : g[p.second]) {
      que.push(P(e.cost, e.to));
    }
  }
  return ret;
}
