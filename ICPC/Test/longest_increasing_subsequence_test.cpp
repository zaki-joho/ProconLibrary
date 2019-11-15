#include "../Others/longest_increasing_subsequence.hpp"

using namespace std;

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3959937
int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  cout << lis(a, n) << endl;
}
