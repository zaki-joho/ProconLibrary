#include "bits/stdc++.h"

// http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3956588
using ll = long long;
#define REP(i, n) for (ll i = 0; i < ll(n); ++i)
using namespace std;

#include "../String/rolling_hash.hpp"

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  string t, p;
  cin >> t >> p;
  RollingHash h(t);
  RollingHash hp(p);
  auto a = hp.query(0, p.size());
  vector<int> ans;
  REP(i, t.size() - p.size() + 1) {
    if (h.query(i, i + p.size()) == a) ans.push_back(i);
  }
  for (auto a : ans) cout << a << endl;
}
