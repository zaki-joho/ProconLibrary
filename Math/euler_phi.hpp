#include "../bits/stdc++.h"

// オイラーの φ 関数
// φ(n) := 1~n の自然数の内, n と互いに素なものの個数
// 1, 1, 2, 2, 4, 2, 6, 4, 6, 4, 10, 4, 12, 6, .....
// m, n が互いに素なら φ(mn) = φ(m)φ(n)

// φ(n) を求める
// O(sqrt(n))
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381745
int eulerPhi(int n) {
  int ret = n;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) ret -= ret / i;
    while (n % i == 0) n /= i;
  }
  if (n > 1) ret -= ret / n;
  return ret;
}

// table 構築
std::vector<int> eulerPhiTable(int n) {
  std::vector<int> ret(n + 1);
  for (int i = 0; i <= n; i++) ret[i] = i;
  for (int i = 2; i <= n; i++) {
    if (ret[i] == i) {
      for (int j = i; j <= n; j += i) {
        ret[j] = ret[j] / i * (i - 1);
      }
    }
  }
  return ret;
}
