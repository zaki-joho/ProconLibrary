#include "../Structure/weighted_union_find.hpp"
#include "../bits/stdc++.h"

using namespace std;

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3959917
int main() {
  int n, q;
  cin >> n >> q;
  WeightedUnionFind uf(n);
  for (int i = 0; i < q; i++) {
    int id;
    cin >> id;
    if (id) {
      int x, y;
      cin >> x >> y;
      if (uf.same(x, y)) {
        cout << -uf.weight(x) + uf.weight(y) << endl;
      } else {
        cout << "?" << endl;
      }
    } else {
      int x, y, z;
      cin >> x >> y >> z;
      uf.unite(x, y, z);
    }
  }
}
