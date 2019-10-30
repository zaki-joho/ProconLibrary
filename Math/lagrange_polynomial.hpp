#include "../bits/stdc++.h"
#include "mod_int.hpp"
// Lagrange 補間
// wikipedia 読んで:
// https://ja.wikipedia.org/wiki/%E3%83%A9%E3%82%B0%E3%83%A9%E3%83%B3%E3%82%B8%E3%83%A5%E8%A3%9C%E9%96%93
// verified: https://atcoder.jp/contests/arc033/submissions/4271515
using ll = long long;

template <int MOD>
ModInt<MOD> lagrangePolynomial(std::vector<ModInt<MOD>> &x,
                               std::vector<ModInt<MOD>> &y, ModInt<MOD> xs) {
  ModInt<MOD> ret = 0;
  int n = x.size();
  for (int i = 0; i < n; i++) {
    ModInt<MOD> s1(1), s2(1);
    for (int j = 0; j < n; j++) {
      if (i != j) {
        s1 *= (xs - x[j]);
        s2 *= (x[i] - x[j]);
      }
    }
    ModInt<MOD> tmp = y[i] * s1;
    tmp *= modPow(s2, ModInt<MOD>(MOD - 2));
    ret += tmp;
  }
  return ret;
}
