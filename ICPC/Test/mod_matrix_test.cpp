#include "../Math/mod_matrix.hpp"

using namespace std;

using ll = long long;

ll h, w, n;
int cs = 1;

int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);

  while (cin >> w >> h >> n, h || w || n) {
    cout << "Case " << cs << ": ";
    cs++;
    bool f = false;
    set<ll> st = {h};
    map<ll, vector<ll>> mp;
    for (int i = 0; i < n; i++) {
      ll x, y;
      cin >> y >> x;
      if (x == 1) continue;
      st.insert(x);
      y--;
      mp[x].push_back(y);
      if (x == h && y == w) {
        f = true;
      }
    }
    if (f) {
      cout << 0 << endl;
      continue;
    }
    vector<vector<ll>> id(w, vector<ll>(w, 0));
    for (int i = 0; i < w; i++) {
      id[i][i] = 1;
      if (i) id[i][i - 1] = 1;
      if (i + 1 < w) id[i][i + 1] = 1;
    }
    vector<ll> x(w, 0);
    x[0] = 1;
    ll pre = 1;
    for (auto v : st) {
      x = modmul(modpow(id, v - pre), x);
      for (auto y : mp[v]) x[y] = 0;
      pre = v;
    }
    cout << x[w - 1] << endl;
  }
}
