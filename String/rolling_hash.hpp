#include "../Others/xor_shift.hpp"
#include "../bits/stdc++.h"

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381829
// moda, modb は桁数増やした方が良いかも.
class RollingHash {
  int n;
  XorShift rnd;
  static const uint64_t moda = (uint64_t)1e9 + 7;
  static const uint64_t modb = (uint64_t)1e9 + 9;
  // static const uint64_t b1 = (uint64_t)17, b2 = (uint64_t)19;
  uint64_t b1 = (uint64_t)rnd.randInt(2, 114514),
           b2 = (uint64_t)rnd.randInt(2, 114514);
  std::vector<uint64_t> a, b, p, q;

 public:
  RollingHash(const std::string &str)
      : n((int)str.size()), a(n + 1, 0), b(n + 1, 0), p(n + 1, 1), q(n + 1, 1) {
    for (int i = 0; i < n; i++) {
      a[i + 1] = (a[i] * b1 + uint64_t(str[i])) % moda;
      b[i + 1] = (b[i] * b2 + uint64_t(str[i])) % modb;
      p[i + 1] = p[i] * b1 % moda;
      q[i + 1] = q[i] * b2 % modb;
    }
  }
  // [l, r) のハッシュ値を取得
  std::pair<uint64_t, uint64_t> query(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    uint64_t h1 = (p[r - l] * a[l] - a[r] + moda) % moda;
    uint64_t h2 = (q[r - l] * b[l] - b[r] + modb) % modb;
    return std::make_pair(h1, h2);
  }
};
