#include "../bits/stdc++.h"
// http://tsutaj.hatenablog.com/entry/2017/03/30/224339
// 区間加算区間和 再帰遅延セグ木 0-indexed
// TODO: 非再帰, template
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3380844
template <typename M>
class LazySegmentTree
{
    int n;
    using type = long long;
    std::vector<type> node, lazy;

    // k-th element 遅延評価
    void eval(int k, int l, int r)
    {
        if (lazy[k] != M::id2())
        {
            node[k] = M::op2(node[k], lazy[k]);

            // 葉ノードでなければ伝播
            if (r - l > 1)
            {
                lazy[2 * k + 1] = M::op3(lazy[2 * k + 1], lazy[k] / 2);
                lazy[2 * k + 2] = M::op3(lazy[2 * k + 2], lazy[k] / 2);
            }

            lazy[k] = M::id2();
        }
    }

  public:
    LazySegmentTree(std::vector<type> v)
    {
        int sz = int(v.size());
        n = 1;
        while (n < sz)
            n *= 2;
        node.resize(2 * n - 1);
        lazy.resize(2 * n - 1, M::id2());

        for (int i = 0; i < sz; i++)
            node[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; i--)
            node[i] = M::op1(node[i * 2 + 1], node[i * 2 + 2]);
    }

    // 区間 op2
    void add(int a, int b, type x, int k = 0, int l = 0, int r = -1)
    {
        if (r < 0)
            r = n;

        eval(k, l, r);

        if (b <= l || r <= a)
            return;

        if (a <= l && r <= b)
        {
            // ここ困る 区間add 用
            lazy[k] += (r - l) * x;
            eval(k, l, r);
        }
        else
        {
            add(a, b, x, 2 * k + 1, l, (l + r) / 2);
            add(a, b, x, 2 * k + 2, (l + r) / 2, r);
            node[k] = M::op1(node[2 * k + 1], node[2 * k + 2]);
        }
    }

    // 区間sum
    type sum(int a, int b, int k = 0, int l = 0, int r = -1)
    {
        if (r < 0)
            r = n;
        if (b <= l || r <= a)
            return M::id1();

        eval(k, l, r);
        if (a <= l && r <= b)
            return node[k];
        type vl = sum(a, b, 2 * k + 1, l, (l + r) / 2);
        type vr = sum(a, b, 2 * k + 2, (l + r) / 2, r);
        return M::op1(vl, vr);
    }
};
