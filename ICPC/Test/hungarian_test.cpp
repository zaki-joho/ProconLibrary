#include "../Graph/hungarian.hpp"
#include "../bits/stdc++.h"

using namespace std;

using ll = long long;
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3955213
int main() {
  int n;
  while (cin >> n, n) {
    vector<vector<ll>> v;
    ll sum = 0;
    for (int i = 0; i < n; i++) {
      ll x, y, z;
      cin >> x >> y >> z;
      vector<ll> tmp = {x, y, z};
      sort(tmp.begin(), tmp.end());
      v.push_back(tmp);
      sum += x * y * z;
    }
    vector<vector<ll>> a(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (v[i][0] < v[j][0] && v[i][1] < v[j][1] && v[i][2] < v[j][2]) {
          a[i][j] = v[i][0] * v[i][1] * v[i][2];
        }
      }
    }
    cout << sum - hungarian(a) << endl;
  }
}
