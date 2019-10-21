#include "../bits/stdc++.h"
#include "../Structure/fenwick_tree.hpp"

using namespace std;

// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3943240#1
void solve_dsl_2_b()
{
    int n, q;
    cin >> n >> q;
    FenwickTree<int> ft(100010);
    for (int i = 0; i < q; i++)
    {
        int com, x, y;
        cin >> com >> x >> y;
        if (com)
        {
            cout << ft.sum(x, y + 1) << endl;
        }
        else
        {
            ft.add(x, y);
        }
    }
}

int main()
{
    solve_dsl_2_b();
}
