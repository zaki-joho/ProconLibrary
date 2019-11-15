#include "../bits/stdc++.h"
// http://kazuma8128.hatenablog.com/entry/2018/05/06/022654
// verified(insert, erase, k-th element):
// https://atcoder.jp/contests/arc033/submissions/4648138 verified(xor minimum):
// https://codeforces.com/contest/947/submission/51609141
class BinaryTrie {
  using T = unsigned;
  // bit 数
  static const int B = 32;
  struct Node {
    // 要素数
    int cnt;
    Node *ch[2];
    Node() : cnt(0) { ch[0] = nullptr, ch[1] = nullptr; }
  };

  Node *root;

  // Node t 以下に 値 val を追加
  Node *add(Node *t, T val, int b = B - 1) {
    if (!t) t = new Node;
    t->cnt += 1;
    if (b < 0) return t;
    bool f = (val >> (T)b) & (T)1;
    t->ch[f] = add(t->ch[f], val, b - 1);
    return t;
  }
  // Node t 以下から値 val を削除
  Node *sub(Node *t, T val, int b = B - 1) {
    // 要素が無ければエラー
    assert(t);
    t->cnt -= 1;
    if (t->cnt == 0) return nullptr;
    if (b < 0) return t;
    bool f = (val >> (T)b) & (T)1;
    t->ch[f] = sub(t->ch[f], val, b - 1);
    return t;
  }
  // Node t 以下の k-th element を取得
  T get(Node *t, int k, int b = B - 1) const {
    assert(t);
    if (b < 0) return 0;
    int m = t->ch[0] ? t->ch[0]->cnt : 0;
    return k < m ? get(t->ch[0], k, b - 1)
                 : get(t->ch[1], k - m, b - 1) | ((T)1 << (T)b);
  }
  // Node t 以下で val と xor するときの最小値取得
  T getMinimum(Node *t, T val, int b = B - 1) const {
    assert(t);
    if (b < 0) return 0;
    bool f = (val >> (T)b) & (T)1;
    f ^= !t->ch[f];
    return getMinimum(t->ch[f], val, b - 1) | ((T)f << (T)b);
  }
  // Node t 以下の val 未満の要素数
  int countLessThan(Node *t, T val, int b = B - 1) const {
    if (!t || b < 0) return 0;
    bool f = (val >> (T)b) & (T)1;
    return (f && t->ch[0] ? t->ch[0]->cnt : 0) +
           countLessThan(t->ch[f], val, b - 1);
  }

 public:
  BinaryTrie() : root(nullptr) {}
  int size() const { return root ? root->cnt : 0; }
  bool empty() const { return !root; }
  // val を集合に1つ追加
  void insert(T val) { root = add(root, val); }
  // val を集合から1つ削除(なければRE)
  void erase(T val) { root = sub(root, val); }
  // 集合内の最大値
  T maximumElement(T mask = 0) const { return getMinimum(root, ~mask); }
  // 集合内の最小値
  T minimumElement(T mask = 0) const { return getMinimum(root, mask); }
  // 集合内で val 以上の要素の最小index
  int lowerBound(T val) const { return countLessThan(root, val); }
  // 集合内で val より大きい要素の最小index
  int upperBound(T val) const { return countLessThan(root, val + 1); }
  // k-th element(0-indexed) を取得
  T get(int k) const {
    assert(0 <= k && k < size());
    return get(root, k);
  }
  // val の個数
  int count(T val) const {
    if (!root) return 0;
    Node *t = root;
    for (int i = B - 1; i >= 0; i--) {
      t = t->ch[(val >> (T)i) & (T)1];
      if (!t) return 0;
    }
    return t->cnt;
  }
};
