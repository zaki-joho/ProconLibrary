#include "bits/stdc++.h"

using namespace std;

// 参考: http://sigma425.hatenablog.com/entries/2014/12/30

using type = int;
static type id() { return INT_MAX; }
static type op(const type &l, const type &r) { return std::min(l, r); }

constexpr int MAX_N = 200010 * 20;

struct Node
{
    Node *lch, *rch;
    type val;
    Node(Node *l, Node *r, int _v)
    {
        lch = l;
        rch = r;
        val = _v;
    }
    Node(Node *l, Node *r)
    {
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

Node *my_new(Node *lch, Node *rch, type val)
{
    return &(pool[sid++] = Node(lch, rch, val));
}

Node *my_new(Node *lch, Node *rch)
{
    return &(pool[sid++] = Node(lch, rch));
}

// update(x, pos, val, l, r) := ノードx で [l, r) に必要なノードを作成する
// return : 自身のノードのポインタ
Node *update(Node *node, int pos, type val, int l, int r)
{
    if (r - l == 1)
    {
        return my_new(nil, nil, val);
    }
    int m = (l + r) / 2;
    if (pos < m)
    {
        return my_new(update(node->lch, pos, val, l, m), node->rch);
    }
    return my_new(node->lch, update(node->rch, pos, val, m, r));
}

type query(Node *node, int a, int b, int l, int r)
{
    if (node == nil)
        return id();
    if (b <= l || r <= a)
        return id();
    if (a <= l && r <= b)
        return node->val;
    int m = (l + r) / 2;
    return op(query(node->lch, a, b, l, m), query(node->rch, a, b, m, r));
}

// https://www.hackerrank.com/contests/happy-query-contest/challenges/minimum-history-query/submissions/code/1317210591
void solve_minimum_history_query()
{
    nil = my_new(0, 0, id());
    nil->lch = nil->rch = nil;
    root[0] = nil;
    int n;
    cin >> n;
    int last_answer = 0;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        root[0] = update(root[0], i, a, 0, n);
    }
    int q1, q2;
    cin >> q1;
    for (int i = 1; i <= q1; i++)
    {
        int p1, x1;
        cin >> p1 >> x1;
        p1--;
        // a[p1] = x1;
        root[i] = update(root[i - 1], p1, x1, 0, n);
    }
    cin >> q2;
    for (int i = 1; i <= q2; i++)
    {
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

int main()
{
    solve_minimum_history_query();
}
