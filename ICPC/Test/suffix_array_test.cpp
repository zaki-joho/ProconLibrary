#include "bits/stdc++.h"

// https://atcoder.jp/contests/kupc2016/submissions/8191225
using namespace std;
#include "../String/suffix_array.hpp"
int main() {
  cin.tie(0);
  ios::sync_with_stdio(false);
  string t;
  cin >> t;
  SuffixArray sa(t);
  auto lcp = sa.getLcp();
  cout << t.size() - *max_element(lcp.begin(), lcp.end()) << endl;
}
