#include "../bits/stdc++.h"
#include "../Structure/heavy_light_decomposition.hpp"
#include "../Structure/range_add_range_sum.hpp"

using namespace std;

// http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3943554
void solve_grl_5_d()
{
    int n;
    cin >> n;
    HLDecomposition hld(n);
    LazySegmentTree lst(n);
    vector<int> par(n, -1);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int c;
            cin >> c;
            hld.add_edge(i, c);
            par[c] = i;
        }
    }
    hld.build();
    int q;
    cin >> q;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 0)
        {
            int v, w;
            cin >> v >> w;
            hld.for_each_edge(par[v], v, [&](int l, int r) {
                lst.update(l, r + 1, w);
            });
            continue;
        }
        int u;
        cin >> u;
        long long ret = 0;
        hld.for_each_edge(0, u, [&](int l, int r) {
            ret += lst.query(l, r + 1);
        });
        cout << ret << endl;
    }
}

// http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3943586
void solve_grl_5_e()
{
    int n;
    cin >> n;
    HLDecomposition hld(n);
    LazySegmentTree lst(n);
    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++)
        {
            int c;
            cin >> c;
            hld.add_edge(i, c);
        }
    }
    hld.build();
    int q;
    cin >> q;
    while (q--)
    {
        int type;
        cin >> type;
        if (type == 0)
        {
            int v, w;
            cin >> v >> w;
            hld.for_each_edge(0, v, [&](int l, int r) {
                lst.update(l, r + 1, w);
            });
            continue;
        }
        int u;
        cin >> u;
        long long ret = 0;
        hld.for_each_edge(0, u, [&](int l, int r) {
            ret += lst.query(l, r + 1);
        });
        cout << ret << endl;
    }
}

// 頂点クエリテストしてない

int main()
{
    solve_grl_5_d();
}
