#include "bits/stdc++.h"

// http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3954111
using namespace std;
#include "../String/aho_corasick.hpp"
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  string t, p;
  cin >> t >> p;
  vector<string> s = {p};
  AhoCorasick<characters> aho(s);
  auto ret = aho.match(t);
  for (auto a : ret[0]) {
    cout << a - p.size() + 1 << endl;
  }
}
