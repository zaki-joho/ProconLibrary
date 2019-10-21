#include "../bits/stdc++.h"
#include "../Structure/lazy_skew_heap.hpp"

using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3943247#1
void solve_itp2_2_c()
{
    int n, q;
    cin >> n >> q;
    vector<LazySkewHeap<int>> que(n);
    while (q--)
    {
        int com;
        cin >> com;
        if (com == 0)
        {
            int t, x;
            cin >> t >> x;
            que[t].push(-x);
        }
        else if (com == 1)
        {
            int t;
            cin >> t;
            if (que[t].empty())
                continue;
            cout << -que[t].top() << endl;
        }
        else
        {
            int t;
            cin >> t;
            if (que[t].empty())
                continue;
            que[t].pop();
        }
    }
}

int main()
{
    solve_itp2_2_c();
}
