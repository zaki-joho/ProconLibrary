#include "../bits/stdc++.h"

struct XorShift {
  using result_type = uint64_t;
  result_type w = 123456789, x = 362436069, y = 521288629, z = 88675123;
  XorShift(result_type seed = time(nullptr)) {
    w = seed;
    x = w << 13;
    y = (w >> 9) ^ (x << 6);
    z = y >> 7;
  }
  result_type rand() {
    result_type t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19) ^ (t ^ (t >> 8)));
  }
  // [min,max] の整数値乱数
  result_type randInt(result_type min = 0, result_type max = 0x7FFFFFFF) {
    return rand() % (max - min + 1) + min;
  }
};

constexpr int MAX_N = 100010;
using ll = long long;
using Graph = std::vector<std::vector<int>>;
XorShift rnd(114514);
std::vector<ll> rnds(MAX_N, -1);

ll isomorphism(int cur, int pre, int depth, const Graph &g, ll mod) {
  if (pre != -1 && g[cur].size() == 1) {
    return 1;
  }
  if (rnds[0] == -1) {
    for (int i = 0; i < MAX_N; i++) {
      rnds[i] = rnd.randInt();
    }
  }
  ll ret = 1;
  for (auto v : g[cur]) {
    if (v == pre) continue;
    ret = ret * (rnds[depth] + isomorphism(v, cur, depth + 1, g, mod)) % mod;
  }
  return ret;
}
