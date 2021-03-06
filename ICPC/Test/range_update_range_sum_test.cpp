#include "../bits/stdc++.h"
#include "../Structure/range_update_range_sum.hpp"

using namespace std;

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3943380
void solve_dsl_2_i()
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
            t++;
            lst.update(s, t, x);
        }
        else
        {
            int s, t;
            cin >> s >> t;
            t++;
            cout << lst.query(s, t) << endl;
        }
    }
}

int main()
{
    solve_dsl_2_i();
}
