#include "../bits/stdc++.h"

template <typename T>
class FenwickTree {
  int n;
  std::vector<T> bt;

 public:
  FenwickTree(int _n) : n(_n), bt(_n, 0) {}

  void add(int pos, const T &w) {
    assert(0 <= pos && pos < n);
    for (int i = pos; i < n; i |= i + 1) bt[i] += w;
  }
  // [0, pos)
  T sum(int pos) {
    assert(0 <= pos && pos <= n);
    T res = 0;
    for (int i = pos - 1; i >= 0; i = (i & (i + 1)) - 1) {
      res += bt[i];
    }
    return res;
  }
  // [l, r)
  T sum(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) + (-sum(l));
  }
};
