#include "../bits/stdc++.h"

// Longest Increasing Subsequencd
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381664
int lis(std::vector<int> &a, int n) {
  const int INF = 1e9;
  std::vector<int> dp(n, INF);
  for (int i = 0; i < n; i++) {
    *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
  }
  return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}

/**
 * ヒストグラム h_1, h_2,..., h_n が与えられる(各幅は1とする)
 * 包含される長方形の内面積最大のものを求める
 * L[i] := (j <= i && h_{j-1} < h_i) となるような最大の j
 * R[i] := (j > i && h_j < h_i) となるような最大の j
 */
template <typename T>
T maxRectangle(std::vector<T> &h) {
  int n = h.size();
  std::vector<int> L(n), R(n);
  std::vector<int> st(n);

  int t = 0;  // stack size
  for (int i = 0; i < n; i++) {
    while (t > 0 && h[st[t - 1]] >= h[i]) t--;
    L[i] = t == 0 ? 0 : (st[t - 1] + 1);
    st[t++] = i;
  }
  t = 0;
  for (int i = n - 1; i >= 0; i--) {
    while (t > 0 && h[st[t - 1]] >= h[i]) t--;
    R[i] = t == 0 ? n : st[t - 1];
    st[t++] = i;
  }

  T ret = 0;
  for (int i = 0; i < n; i++) ret = std::max(ret, h[i] * (R[i] - L[i]));
  return ret;
}
