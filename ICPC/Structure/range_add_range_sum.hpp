#include "../bits/stdc++.h"
// range add range sum
class LazySegmentTree {
  int n;
  using T1 = int;
  using T2 = int;
  std::vector<T1> node;
  std::vector<T2> lazy;

  // 遅延評価
  void eval(int k, int l, int r) {
    // 遅延配列が空なら終了
    if (lazy[k] == 0) return;
    // 遅延配列を適用
    node[k] = node[k] + lazy[k];
    if (r - l > 1) {
      lazy[2 * k + 1] = lazy[2 * k + 1] + lazy[k] / 2;
      lazy[2 * k + 2] = lazy[2 * k + 2] + lazy[k] / 2;
    }
    // 遅延配列初期化
    lazy[k] = 0;
  }

 public:
  LazySegmentTree(int _n) {
    int sz = _n;
    n = 1;
    while (n < sz) n *= 2;
    // 配列初期化
    node.resize(2 * n - 1, 0);
    lazy.resize(2 * n - 1, 0);
  }
  LazySegmentTree(int _n, T1 _v) {
    int sz = _n;
    n = 1;
    while (n < sz) n *= 2;
    node.resize(2 * n - 1, 0);
    lazy.resize(2 * n - 1, 0);

    for (int i = 0; i < sz; i++) node[i + n - 1] = _v;
    for (int i = n - 2; i >= 0; i--)
      node[i] = node[i * 2 + 1] + node[i * 2 + 2];
  }

  // 半開区間 [a, b) に対して値 val を反映させる
  void update(int a, int b, T2 val, int l = 0, int r = -1, int k = 0) {
    if (r < 0) r = n;
    // ノード k で遅延評価
    eval(k, l, r);
    if (b <= l || r <= a) return;
    // 区間が被覆されている場合
    if (a <= l && r <= b) {
      // 遅延配列更新, 評価
      lazy[k] = lazy[k] + (r - l) * val;
      eval(k, l, r);
    } else {
      // 子ノードの値を評価し, 更新
      int mid = (l + r) / 2;
      update(a, b, val, l, mid, 2 * k + 1);
      update(a, b, val, mid, r, 2 * k + 2);
      node[k] = node[2 * k + 1] + node[2 * k + 2];
    }
  }

  // 半開区間 [a, b) に対してクエリを投げる
  T1 query(int a, int b, int l = 0, int r = -1, int k = 0) {
    if (r < 0) r = n;
    eval(k, l, r);
    // 範囲外なら単位元返す
    if (b <= l || r <= a) return 0;
    if (a <= l && r <= b) return node[k];
    int mid = (l + r) / 2;
    T1 vl = query(a, b, l, mid, 2 * k + 1);
    T1 vr = query(a, b, mid, r, 2 * k + 2);
    return vl + vr;
  }
};
