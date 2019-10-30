#include "../bits/stdc++.h"
// 各連結成分内の要素数が取得できる UnionFind
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3380552
class UnionFind {
  std::vector<int> data;
  int root_count;

 public:
  UnionFind(int size) : data(size, -1), root_count(size) {}
  bool unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x != y) {
      if (data[y] < data[x]) std::swap(x, y);
      data[x] += data[y];
      data[y] = x;
      root_count--;
    }
    return x != y;
  }
  bool find(int x, int y) { return root(x) == root(y); }
  int root(int x) { return data[x] < 0 ? x : data[x] = root(data[x]); }
  int size(int x) { return -data[root(x)]; }
  int count() const { return root_count; }
};
