#include "../bits/stdc++.h"
using namespace std;
class RollingHash {
  using ull = uint64_t;
  int n;
  mt19937 rnd;
  static const ull moda = (ull)1e9 + 7;
  static const ull modb = (ull)1e9 + 9;
  ull b1 = (ull)rnd(), b2 = (ull)rnd();
  std::vector<ull> a, b, p, q;

public:
  RollingHash(const std::string &str) : n((int)str.size()), a(n + 1, 0), b(n + 1, 0), p(n + 1, 1), q(n + 1, 1) {
    for (int i = 0; i < n; i++) {
      a[i + 1] = (a[i] * b1 + ull(str[i])) % moda;
      b[i + 1] = (b[i] * b2 + ull(str[i])) % modb;
      p[i + 1] = p[i] * b1 % moda;
      q[i + 1] = q[i] * b2 % modb;
    }
  }
  // [l, r) のハッシュ値を取得
  std::pair<ull, ull> query(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    ull h1 = (p[r - l] * a[l] - a[r] + moda) % moda;
    ull h2 = (q[r - l] * b[l] - b[r] + modb) % modb;
    return std::make_pair(h1, h2);
  }
};