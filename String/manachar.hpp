#include "../bits/stdc++.h"
// 奇数長回文のみ検出 O(|s|)
// r[i] := s[i] を中心とする最長の回文半径
// https://snuke.hatenablog.com/entry/2014/12/02/235837
std::vector<int> manachar(const std::string &s) {
  int n = s.length();
  std::vector<int> r(n);
  int i = 0, j = 0;  // i:位置 j:長さ
  while (i < n) {
    while (i - j >= 0 && i + j < n && s[i - j] == s[i + j]) {
      j++;
    }
    r[i] = j;
    int k = 1;
    while (i - k >= 0 && i + k < n && k + r[i - k] < j) {
      r[i + k] = r[i - k];
      k++;
    }
    i += k;
    j -= k;
  }
  return r;
}
