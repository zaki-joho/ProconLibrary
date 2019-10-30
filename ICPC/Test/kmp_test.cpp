#include "bits/stdc++.h"
// http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3954691
using namespace std;
#include "../String/kmp.hpp"
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  string t, p;
  cin >> t >> p;
  string s = p + "@" + t;
  auto a = kmp(s);
  vector<int> ans;
  for (int i = (int)p.size() + 1; i < (int)s.size(); ++i) {
    if (a[i] >= (int)p.size()) ans.push_back(i - p.size() - p.size());
  }
  for (auto b : ans) {
    cout << b << endl;
  }
}
