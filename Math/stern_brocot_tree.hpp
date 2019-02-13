#include "../bits/stdc++.h"
// https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree
// 有理数に対する無限の高さを持つ二分探索木
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3283559
// ここでは u/v < sqrt(p) < x/y となる u, v, x, y (<= n) の内, 
// u/v が最大かつ x/y が採用となるような組を探す (p, n <= 10000, p : prime)
using type = long long;
type p, n;
type u, v, x, y;

void sternBrocot(type pl = 0, type ql = 1, type pr = 1, type qr = 0)
{
    type pm = pl + pr, qm = ql + qr;
    if (pm > n || qm > n)
        return;
    if (p * (qm * qm) < pm * pm)
    {
        x = pm;
        y = qm;
        sternBrocot(pl, ql, pm, qm);
    }
    else if (p * (qm * qm) > pm * pm)
    {
        u = pm;
        v = qm;
        sternBrocot(pm, qm, pr, qr);
    }
    return;
}
