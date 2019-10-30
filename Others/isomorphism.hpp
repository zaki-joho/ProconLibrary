// verified: https://csacademy.com/submission/2149615/
#include "../bits/stdc++.h"
#include "xor_shift.hpp"

// 乱数でグラフの同型性判定
// Hack 可能.
class Isomorphism {
  using Graph = std::vector<std::vector<int>>;
  using ll = long long;
  const int MOD = 1e9 + 7;
  int n;
  XorShift xs;
  Graph graph;
  // rnd[i]   := 深さ i の頂点の乱数
  // hash[j]  := 頂点 j の乱数
  std::vector<ll> rnd, hash;
  ll dfs(int cur, int pre, int dep) {
    int sz = graph[cur].size();
    if (sz == 1 && pre != -1) {
      return hash[cur] = 1;
    }
    ll res = 1;
    for (int i = 0; i < sz; i++) {
      int next = graph[cur][i];
      if (next == pre) continue;
      res *= (rnd[dep] + dfs(next, cur, dep + 1));
      res %= MOD;
    }
    return hash[cur] = res;
  }

 public:
  Isomorphism(int _n)
      : n(_n), xs(XorShift()), rnd(n, -1), hash(n, -1), graph(n) {
    for (int i = 0; i < n; i++) {
      rnd[i] = xs.randInt(0, MOD - 1);
    }
  }

  void add_edge(int u, int v) { graph[u].push_back(v); }
  ll getHash(int root = 0) { return dfs(root, -1, 0); }

  ll getNodeHash(int node = 0) { return hash[node]; }
};
