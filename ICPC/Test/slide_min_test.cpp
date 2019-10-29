#include "../Others/slide_min.hpp"
#include "../bits/stdc++.h"

using namespace std;

template <typename T>
void printv(const vector<T> &v) {
  int sz = v.size();
  for (int i = 0; i < sz; i++) {
    cout << v[i] << " \n"[i == sz - 1];
  }
}

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3958484
int main() {
  int N, L;
  cin >> N >> L;
  SlideMinimum<int> sm(L);
  vector<int> ret;
  for (int i = 0; i < N; i++) {
    int a;
    cin >> a;
    int t = sm.query(a);
    if (i >= L - 1) ret.push_back(t);
  }
  printv(ret);
}
