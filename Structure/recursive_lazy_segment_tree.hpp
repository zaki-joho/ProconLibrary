#include "../bits/stdc++.h"
// http://tsutaj.hatenablog.com/entry/2017/03/30/224339
// 区間加算区間和 再帰遅延セグ木 0-indexed
// TODO: 非再帰, template
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3380844
class LazySegmentTree
{
    int n;
    using type = long long;
    std::vector<type> node, lazy;

    // k-th element 遅延評価
    void eval(int k, int l, int r)
    {
        if (lazy[k])
        {
            node[k] += lazy[k];

            // 葉ノードでなければ伝播
            if (r - l > 1)
            {
                lazy[2 * k + 1] += lazy[k] / 2;
                lazy[2 * k + 2] += lazy[k] / 2;
            }

            lazy[k] = 0;
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
        lazy.resize(2 * n - 1, 0);

        for (int i = 0; i < sz; i++)
            node[i + n - 1] = v[i];
        for (int i = n - 2; i >= 0; i--)
            node[i] = node[i * 2 + 1] + node[i * 2 + 2];
    }

    // 区間add
    void add(int a, int b, type x, int k = 0, int l = 0, int r = -1)
    {
        if (r < 0)
            r = n;

        eval(k, l, r);

        if (b <= l || r <= a)
            return;

        if (a <= l && r <= b)
        {
            lazy[k] += (r - l) * x;
            eval(k, l, r);
        }
        else
        {
            add(a, b, x, 2 * k + 1, l, (l + r) / 2);
            add(a, b, x, 2 * k + 2, (l + r) / 2, r);
            node[k] = node[2 * k + 1] + node[2 * k + 2];
        }
    }

    // 区間sum
    type sum(int a, int b, int k = 0, int l = 0, int r = -1)
    {
        if (r < 0)
            r = n;
        if (b <= l || r <= a)
            return 0;

        eval(k, l, r);
        if (a <= l && r <= b)
            return node[k];
        type vl = sum(a, b, 2 * k + 1, l, (l + r) / 2);
        type vr = sum(a, b, 2 * k + 2, (l + r) / 2, r);
        return vl + vr;
    }
};
