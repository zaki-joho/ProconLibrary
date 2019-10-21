#include "../bits/stdc++.h"
#include "../Structure/monoid.hpp"
#include "../Structure/segment_tree.hpp"

using namespace std;

void solve_dsl_2_a()
{ // range min
    int n, q;
    cin >> n >> q;
    SegmentTree<RangeMinimumQuery> st(n);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 0)
        {
            int index, x;
            cin >> index >> x;
            st.update(index, x);
        }
        else
        {
            int s, t;
            cin >> s >> t;
            t++;
            cout << st.query(s, t) << endl;
            ;
        }
    }
}

void solve_dsl_2_b()
{ // range sum
    int n, q;
    cin >> n >> q;
    SegmentTree<RangeSumQuery> st(n);
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 0)
        {
            int index, x;
            cin >> index >> x;
            index--;
            st.operation(index, x);
        }
        else
        {
            int s, t;
            cin >> s >> t;
            s--;
            cout << st.query(s, t) << endl;
            ;
        }
    }
}

int main()
{
    solve_dsl_2_a();
}
