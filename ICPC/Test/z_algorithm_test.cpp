#include "bits/stdc++.h"
// https://atcoder.jp/contests/arc055/submissions/8142114
using namespace std;
using ll = long long;
#define REP(i, n) for (ll i = 0; i < ll(n); ++i)
#define ALL(v) v.begin(), v.end()

#include "../String/z_algorithm.hpp"

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  string s;
  cin >> s;
  string rs = s;
  reverse(ALL(rs));
  auto z = z_algorithm(s), rz = z_algorithm(rs);
  int n = s.size();
  ll ans = 0;
  REP(i, n) {
    if (i <= n - i) continue;
    ll a = z[i], b = rz[n - i];
    ans += max(0ll, min(a, n - i - 1) - max(1ll, (n - i - b)) + 1);
  }
  cout << ans << endl;
}
