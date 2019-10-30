#include "../bits/stdc++.h"
// 重み付き UnionFind
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3380602
class WeightedUnionFind {
  std::vector<int> par;  // 親の番号
  std::vector<int> ws;   // 親との重みの差

 public:
  WeightedUnionFind(int n) : par(n, -1), ws(n, 0) {}

  // x の親を返す
  int find(int x) {
    if (par[x] < 0) {
      return x;
    } else {
      int parent = find(par[x]);
      ws[x] += ws[par[x]];
      return par[x] = parent;
    }
  }

  // x の重み(親との相対値)を返す
  int weight(int x) {
    find(x);
    return ws[x];
  }

  // 頂点 x, y を (xの重み) + w = (yの重み) となるように Unite
  bool unite(int x, int y, int w) {
    w += weight(x);
    w -= weight(y);
    x = find(x);
    y = find(y);

    if (x != y) {
      if (par[y] < par[x]) {  // 多い方が根になるようにスワップする.
        int tmp = x;
        x = y;
        y = tmp;
        w = -w;
      }
      par[x] += par[y];
      par[y] = x;
      ws[y] = w;
      return true;
    } else {
      return false;
    }
  }

  bool same(int x, int y) { return find(x) == find(y); }

  void init(int size) {
    for (int i = 0; i < size; i++) {
      par[i] = -1;
      ws[i] = 0;
    }
  }
};
