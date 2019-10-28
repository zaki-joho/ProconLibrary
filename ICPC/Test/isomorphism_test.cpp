#include "../Graph/isomorphism.hpp"
#include "../bits/stdc++.h"

using namespace std;

constexpr ll mod = 1e9 + 7;

// verified: https://csacademy.com/contest/archive/task/binary-isomorphism
// https://csacademy.com/submission/2637965/
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    Graph g1(n), g2(n);
    int r1 = -1, r2 = -1;
    for (int i = 0; i < n; i++) {
      int a;
      cin >> a;
      if (a == 0)
        r1 = i;
      else {
        a--;
        g1[a].push_back(i);
        g1[i].push_back(a);
      }
    }
    for (int i = 0; i < n; i++) {
      int a;
      cin >> a;
      if (a == 0)
        r2 = i;
      else {
        a--;
        g2[a].push_back(i);
        g2[i].push_back(a);
      }
    }
    cout << (isomorphism(r1, -1, 0, g1, mod) == isomorphism(r2, -1, 0, g2, mod)
                 ? 1
                 : 0)
         << endl;
  }
}
