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

// verified: https://yukicoder.me/submissions/392372
void solve_yukicoder_399()
{
    using ll = long long;
    int n;
    cin >> n;
    HLDecomposition hld(n);
    LazySegmentTree lst(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        hld.add_edge(u, v);
    }
    hld.build();
    for (int i = 0; i < n; i++)
    {
        hld.for_each_vertex(i, i, [&](int l, int r) {
            lst.update(l, r + 1, 1);
        });
    }
    int q;
    cin >> q;
    ll ret = 0;
    while (q--)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        hld.for_each_vertex(a, b, [&](int l, int r) {
            ret += lst.query(l, r + 1);
        });
        hld.for_each_vertex(a, b, [&](int l, int r) {
            lst.update(l, r + 1, 1);
        });
    }
    cout << ret << endl;
}

int main()
{
    solve_yukicoder_399();
}
