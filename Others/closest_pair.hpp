#include "../bits/stdc++.h"
// N 頂点の最近点対距離を O(NlogN) で求める
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3380540
using ld = long double;
using P = std::pair<ld, ld>;
const ld INF = 1e15;

constexpr int MAX_N = 100000;
int N;
P A[MAX_N];

bool compareY(P a, P b) { return a.second < b.second; }

ld closestPair(P *a, int n) {
  if (n <= 1) return INF;
  int m = n / 2;
  ld x = a[m].first;
  ld d = std::min(closestPair(a, m), closestPair(a + m, n - m));
  std::inplace_merge(a, a + m, a + n, compareY);
  // a は y の昇順

  std::vector<P> b;
  for (int i = 0; i < n; i++) {
    if (fabs(a[i].first - x) >= d) continue;

    for (int j = 0; j < int(b.size()); j++) {
      ld dx = a[i].first - b[int(b.size()) - j - 1].first;
      ld dy = a[i].second - b[int(b.size()) - j - 1].second;
      if (dy >= d) break;
      d = std::min(d, sqrt(dx * dx + dy * dy));
    }
    b.push_back(a[i]);
  }
  return d;
}
