#include "../Structure/persistent_segment_tree.hpp"

using namespace std;

// 参考: http://sigma425.hatenablog.com/entries/2014/12/30
// verified: https://www.hackerrank.com/contests/happy-query-contest/challenges/minimum-history-query/submissions/code/1317210591
void solve_minimum_history_query() {
  nil = my_new(0, 0, id());
  nil->lch = nil->rch = nil;
  root[0] = nil;
  int n;
  cin >> n;
  int last_answer = 0;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    root[0] = update(root[0], i, a, 0, n);
  }
  int q1, q2;
  cin >> q1;
  for (int i = 1; i <= q1; i++) {
    int p1, x1;
    cin >> p1 >> x1;
    p1--;
    // a[p1] = x1;
    root[i] = update(root[i - 1], p1, x1, 0, n);
  }
  cin >> q2;
  for (int i = 1; i <= q2; i++) {
    int k, l, r;
    cin >> k >> l >> r;
    k ^= last_answer;
    l ^= last_answer;
    r ^= last_answer;
    l--;
    // min{a_l...a_r}
    int ret = query(root[k], l, r, 0, n);
    cout << ret << endl;
    last_answer = ret;
  }
}

int main() { solve_minimum_history_query(); }
