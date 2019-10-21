#include "../bits/stdc++.h"
#include "../Structure/range_add_range_sum.hpp"

using namespace std;

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3943377
void solve_dsl_2_g()
{
    int n, q;
    cin >> n >> q;
    LazySegmentTree lst(n);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 0)
        {
            int s, t, x;
            cin >> s >> t >> x;
            s--;
            lst.update(s, t, x);
        }
        else
        {
            int s, t;
            cin >> s >> t;
            s--;
            cout << lst.query(s, t) << endl;;
        }
    }
}

int main()
{
    solve_dsl_2_g();
}
