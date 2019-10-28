#include "bits/stdc++.h"
// https://atcoder.jp/contests/ukuku09/submissions/8190487
using ll = long long;
#define REP(i, n) for (ll i = 0; i < ll(n); ++i)

using namespace std;

#include "../String/manachar.hpp"
#include "../Structure/monoid.hpp"
#include "../Structure/segment_tree.hpp"

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  int n, q;
  cin >> n >> q;
  string s;
  cin >> s;
  auto v = manachar(s);
  SegmentTree<RangeMaximumQuery> st(n);
  REP(i, n) st.update(i, v[i]);
  REP(aa, q) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;
    int lb = 1, ub = (r - l + 2) / 2 + 1;
    while (ub - lb > 1) {
      int mid = (ub + lb) / 2;
      int x = st.query(l + mid - 1, r - mid + 2);
      if (x >= mid)
        lb = mid;
      else
        ub = mid;
    }
    cout << lb * 2 - 1 << endl;
  }
}
