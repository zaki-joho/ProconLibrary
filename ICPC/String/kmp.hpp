#include "../bits/stdc++.h"
using namespace std;

// http://potetisensei.hatenablog.com/entry/2017/07/10/174908
// verified : http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3954691
vector<int> kmp(const string &s) {
  int n = s.size();
  vector<int> a(n + 1);
  a[0] = -1;
  int j = -1;
  for (int i = 0; i < n; ++i) {
    while (j >= 0 && s[i] != s[j]) j = a[j];
    ++j;
    if (s[i + 1] == s[j])
      a[i + 1] = a[j];
    else
      a[i + 1] = j;
  }
  vector<int> ret(n);
  for (int i = 0; i < n; ++i) {
    ret[i] = a[i + 1];
  }
  return ret;
}