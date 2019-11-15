#include "../../bits/stdc++.h"
#include "../graph.hpp"

// 単一始点最短経路 最悪O(EV) だが bellmann-ford より速い
// O(E) になったりならなかったりする. 負閉路もok
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3380678
std::vector<int> spfa(const Graph &g, int s) {
  int n = g.size();
  std::vector<int> d(n, INF);
  std::vector<int> in_q(n, 0), count(n, 0);
  std::queue<int> que;
  d[s] = 0;
  que.push(s);
  in_q[s] = 1;
  count[s]++;
  while (!que.empty()) {
    int v = que.front();
    que.pop();
    in_q[v] = 0;
    for (const auto &e : g[v]) {
      if (d[v] != INF && d[e.to] > d[v] + e.cost) {
        d[e.to] = d[v] + e.cost;
        if (!in_q[e.to]) {
          que.push(e.to);
          in_q[e.to] = 1;
          if (++count[e.to] >= n) {
            return std::vector<int>();
          }
        }
      }
    }
  }
  return d;
}
