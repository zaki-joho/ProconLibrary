#include "../bits/stdc++.h"

// Longest Increasing Subsequencd
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381664
int lis(std::vector<int> &a, int n)
{
    const int INF = 1e9;
    std::vector<int> dp(n, INF);
    for (int i = 0; i < n; i++)
    {
        *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
    }
    return lower_bound(dp.begin(), dp.end(), INF) - dp.begin();
}

// 長方形面積
