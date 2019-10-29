#include "../bits/stdc++.h"
using namespace std;

// 返り値: a[i]=s[0,i]のsuffixとpreffixが最大何文字共通するか
// ただし、a[i]<i+1である(s[0,i]をとってくれば一致するので)
/*
 ex.
 aabaabaaa
 010123452
*/
// 計算量 O(|s|)

// 文字列tからpを見つけたい場合、p+'$'+tとしてkmpすればできる
// s[0,i]の最小の周期はi-kmp[i]+1
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