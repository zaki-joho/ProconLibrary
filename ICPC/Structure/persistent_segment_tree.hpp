#include "../bits/stdc++.h"

using type = int;
static type id() { return 1e9; }
static type op(const type &l, const type &r) { return std::min(l, r); }

constexpr int MAX_N = 200010 * 20;

struct Node {
  Node *lch, *rch;
  type val;
  Node(Node *l, Node *r, int _v) {
    lch = l;
    rch = r;
    val = _v;
  }
  Node(Node *l, Node *r) {
    lch = l;
    rch = r;
    val = op(lch->val, rch->val);
  }
  Node() {}
};

Node pool[MAX_N];
Node *root[100010];
Node *nil;
int sid = 0;
// nil = my_new(0, 0, id());
// nil->lch = nil->rch = nil;
// root[0] = nil;

Node *my_new(Node *lch, Node *rch, type val) {
  return &(pool[sid++] = Node(lch, rch, val));
}

Node *my_new(Node *lch, Node *rch) { return &(pool[sid++] = Node(lch, rch)); }

// update(x, pos, val, l, r) := ノードx で [l, r) に必要なノードを作成する
// return : 自身のノードのポインタ
Node *update(Node *node, int pos, type val, int l, int r) {
  if (r - l == 1) {
    return my_new(nil, nil, val);
  }
  int m = (l + r) / 2;
  if (pos < m) {
    return my_new(update(node->lch, pos, val, l, m), node->rch);
  }
  return my_new(node->lch, update(node->rch, pos, val, m, r));
}

type query(Node *node, int a, int b, int l, int r) {
  if (node == nil) return id();
  if (b <= l || r <= a) return id();
  if (a <= l && r <= b) return node->val;
  int m = (l + r) / 2;
  return op(query(node->lch, a, b, l, m), query(node->rch, a, b, m, r));
}
