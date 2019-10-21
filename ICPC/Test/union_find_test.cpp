#include "../bits/stdc++.h"
#include "../Structure/union_find.hpp"

using namespace std;

void solve_dsl_1_a()
{
    int n, q;
    cin >> n >> q;
    UnionFind uf(n);
    for (int i = 0; i < q; i++)
    {
        int com, x, y;
        cin >> com >> x >> y;
        if (com == 0)
            uf.unite(x, y);
        else
            cout << (uf.find(x, y) ? 1 : 0) << endl;
    }
}

int main()
{
    solve_dsl_1_a();
}
