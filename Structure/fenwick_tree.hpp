#include "../bits/stdc++.h"
// http://hos.ac/slides/20140319_bit.pdf
// add(pos, w) := v[pos] += w
// sum(l, r) := v[l] + ... + v[r - 1]
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3380704#1
template <typename T>
class FenwickTree {
  int n;
  std::vector<T> bit;

 public:
  FenwickTree(int _n) : n(_n), bit(_n, 0) {}

  void add(int pos, const T &w) {
    assert(0 <= pos && pos < n);
    for (int i = pos; i < n; i |= i + 1) bit[i] += w;
  }
  // v[0] + ... + v[pos-1]
  T sum(int pos) {
    assert(0 <= pos && pos <= n);
    T res = 0;
    for (int i = pos - 1; i >= 0; i = (i & (i + 1)) - 1) {
      res += bit[i];
    }
    return res;
  }
  T sum(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    return sum(r) + (-sum(l));
  }
};
