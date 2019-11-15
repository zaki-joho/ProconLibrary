#include "../bits/stdc++.h"

// 最大流(Ford Fulkerson)
// O(FE)
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3633122
class FordFulkerson {
  using type = int;
  const int INF = 1e9;
  struct Edge {
    // 行き先, 容量, 逆辺
    int to;
    type cap;
    int rev;
    Edge(int _t, type _c, int _r) : to(_t), cap(_c), rev(_r) {}
  };

  using Graph = std::vector<std::vector<Edge>>;
  int V;
  Graph G;
  // dfs で訪問済みか
  std::vector<bool> usd;

  // 増加パスを dfs で探す
  type dfs(int v, int t, type f) {
    if (v == t) return f;
    usd[v] = true;
    for (auto &e : G[v]) {
      if (!usd[e.to] && e.cap > 0) {
        auto d = dfs(e.to, t, std::min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

 public:
  FordFulkerson(int _v) : V(_v), G(_v), usd(_v) {}
  void add(int from, int to, type cap) {
    G[from].push_back(Edge{to, cap, (int)G[to].size()});
    G[to].push_back(Edge{from, 0, (int)G[from].size() - 1});
  }
  // s->t の最大流を求める
  type maxFlow(int s, int t) {
    type ret = 0;
    while (true) {
      for (int i = 0; i < (int)G.size(); i++) usd[i] = false;
      type f = dfs(s, t, INF);
      if (f == 0) return ret;
      ret += f;
    }
  }
};
