#include "../Math/number_theoretic_transform.hpp"
#include "../bits/stdc++.h"

using namespace std;

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3955054
int main() {
  int n, m, k, l;
  cin >> n >> m >> k >> l;
  vector<string> s(n);
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  string com;
  cin >> com;
  int x = 0, y = 0;
  vector<vector<int>> cnt(m, vector<int>(m, 0));
  for (int i = 0; i < l; i++) {
    if (com[i] == 'U')
      x--;
    else if (com[i] == 'D')
      x++;
    else if (com[i] == 'R')
      y++;
    else
      y--;
    cnt[x][y]++;
  }
  vector<int> A(m * m, 0), B(m * m, 0);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (s[i][j] == 'X') A[i + j * m] = 1;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < m; j++) B[i + j * m] = cnt[i][j];
  NTT ntt;
  auto ret = ntt.convolution(A, B);
  // printv(ret);
  int sum = 0;
  for (const auto &v : ret) {
    if (v >= k) sum++;
  }
  cout << sum << endl;
}
