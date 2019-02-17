#include "../bits/stdc++.h"
// http://tsutaj.hatenablog.com/entry/2017/03/30/224339
// 区間加算区間和 再帰遅延セグ木 0-indexed
// TODO: 非再帰, template
// (verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3380844)
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3386788
template <typename M>
class LazySegmentTree
{
    int n;
    using T = typename M::t1;
    std::vector<T> node, lazy;
    std::vector<bool> upd;

    void eval(int k, int l, int r)
    {
        if (!upd[k])
            return;
        node[k] = M::op2(node[k], lazy[k]);
        if (r - l > 1)
        {
            lazy[2 * k + 1] = M::op3(lazy[2 * k + 1], lazy[k]);
            lazy[2 * k + 2] = M::op3(lazy[2 * k + 2], lazy[k]);
            upd[2 * k + 1] = upd[2 * k + 2] = true;
        }
        lazy[k] = M::id2();
        upd[k] = false;
    }

  public:
    LazySegmentTree(std::vector<T> &v)
    {
        int sz = int(v.size());
        n = 1;
        while (n < sz)
            n *= 2;
        node.resize(2 * n + 1, M::id1());
        lazy.resize(2 * n + 1, M::id2());
        upd.resize(2 * n + 1, false);

        for (int i = 0; i < sz; i++)
            node[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; i--)
            node[i] = M::op1(node[i * 2 + 1], node[i * 2 + 2]);
    }

    // 半開区間 [a, b) に対して値 val を反映させる
    void update(int a, int b, T val, int l = 0, int r = -1, int k = 0)
    {
        if (r < 0)
            r = n;
        eval(k, l, r);
        if (b <= l || r <= a)
            return;
        if (a <= l && r <= b)
        {
            lazy[k] = M::op2(lazy[k], val);
            upd[k] = true;
            eval(k, l, r);
        }
        else
        {
            int mid = (l + r) / 2;
            update(a, b, val, l, mid, 2 * k + 1);
            update(a, b, val, mid, r, 2 * k + 2);
            node[k] = M::op1(node[2 * k + 1], node[2 * k + 2]);
        }
    }

    // 半開区間 [a, b) に対してクエリを投げる
    T query(int a, int b, int l = 0, int r = -1, int k = 0)
    {
        if (r < 0)
            r = n;
        eval(k, l, r);
        if (b <= l || r <= a)
            return M::id1();
        if (a <= l && r <= b)
            return node[k];
        int mid = (l + r) / 2;
        T vl = query(a, b, l, mid, 2 * k + 1);
        T vr = query(a, b, mid, r, 2 * k + 2);
        return M::op1(vl, vr);
    }
};
