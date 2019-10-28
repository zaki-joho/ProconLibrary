#include "../bits/stdc++.h"

class LiChaoTree {
  using T = long long;
  using Line = std::pair<T, T>;
  const T inf = 1e15;
  // 最小化?
  bool isMinimum;
  int n;
  // 各区間には, その区間で最小(or最大)を取りうる直線を保持する
  std::vector<Line> node;
  std::vector<int> usd;

  static inline T f(const Line &line, T x) {
    return line.first * x + line.second;
  }

  // [l, r) に Line を追加, 現在ノードk
  void add(int k, int l, int r, Line line) {
    while (r - l > 0) {
      if (!usd[k]) {
        node[k] = line;
        usd[k] = true;
        return;
      }
      int m = (l + r) / 2;
      bool left = (f(line, l) < f(node[k], l));
      bool mid = (f(line, m) < f(node[k], m));
      bool right = (f(line, r) < f(node[k], r));
      if (!isMinimum) {
        left = !left;
        mid = !mid;
        right = !right;
      }
      if (left && right) {
        node[k] = line;
        return;
      }
      if (!left && !right) {
        return;
      }
      if (mid) {
        swap(line, node[k]);
      }
      if (left != mid) {
        k = 2 * k + 1;
        r = m;
      } else {
        k = 2 * k + 2;
        l = m;
      }
    }
  }

 public:
  // [0, n] 用の木を作る
  LiChaoTree(int _n, bool isMin = true) : isMinimum(isMin) {
    n = 1;
    while (n < _n) n *= 2;
    node.resize(2 * n - 1, Line(0, isMin ? inf : -inf));
    usd.resize(2 * n - 1, false);
  }
  //　ax + b を追加する
  void add(T a, T b) {
    add(0, 0, n, Line(a, b));
    return;
  }
  T get(T x) {
    int k = x + (n - 1);
    T ret = usd[k] ? f(node[k], x) : (isMinimum ? inf : -inf);
    while (k > 0) {
      k = (k - 1) / 2;
      if (usd[k]) {
        ret = isMinimum ? std::min(ret, f(node[k], x))
                        : std::max(ret, f(node[k], x));
      }
    }
    return ret;
  }
};
