#include "../bits/stdc++.h"
#include "../Structure/li_chao_tree.hpp"

using namespace std;

// https://yukicoder.me/submissions/392548
void solve_yukicoder_703()
{
    using ll = long long;
    const ll inf = 1e15;
    int n;
    cin >> n;
    vector<ll> a(n+1), x(n+1), y(n+1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> x[i];
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> y[i];
    }
    LiChaoTree cht(100010);
    vector<ll> dp(n + 1, inf);
    dp[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cht.add(-2 * x[i], x[i] * x[i] + y[i] * y[i] + dp[i-1]);
        dp[i] = cht.get(a[i]) + a[i] * a[i];
        //cerr << dp[i] << endl;
    }
    cout << dp[n] << endl;
}

int main()
{
    solve_yukicoder_703();
}
