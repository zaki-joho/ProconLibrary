#include "../bits/stdc++.h"
#include "../Structure/range_add_range_min.hpp"

using namespace std;

void solve_dsl_2_h()
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
    solve_dsl_2_h();
}
