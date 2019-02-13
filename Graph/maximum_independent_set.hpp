#include "../bits/stdc++.h"
// 最大独立集合問題 V=40 ぐらいまで
// 最小頂点被覆問題と等価
// 補グラフの最大クリーク問題と等価
// 2部グラフ上の最大独立集合問題 = 頂点数 - 最大マッチング
/*
int popcount(unsigned long long a) {
    a = (a & 0x5555555555555555) + (a >> 1 & 0x5555555555555555);
    a = (a & 0x3333333333333333) + (a >> 2 & 0x3333333333333333);
    a = (a & 0x0f0f0f0f0f0f0f0f) + (a >> 4 & 0x0f0f0f0f0f0f0f0f);
    a = (a & 0x00ff00ff00ff00ff) + (a >> 8 & 0x00ff00ff00ff00ff);
    a = (a & 0x0000ffff0000ffff) + (a >> 16 & 0x0000ffff0000ffff);
    return (a & 0xffffffff) + (a >> 32);
}

int maximumIndependentSet(const std::vector<long long> &g)
{
    int n = g.size(), res = 0;
    std::function<void(long long, int)> dfs = [&](long long remain, int cnt) {
        for (bool update = true; update;)
        {
            update = false;
            for (int i = 0; i < n; i++)
                if (remain & (1LL << i))
                {
                    int deg = popcount(remain & g[i]);
                    if (deg <= 1)
                    {
                        cnt++;
                        remain &= ~((1LL << i) | g[i]);
                        update = true;
                    }
                }
        }
        res = std::max(res, cnt);
        if (remain)
        {
            int k = __builtin_ctzll(remain);
            dfs(remain & ~(1LL << k), cnt);
            dfs(remain & ~(g[k] | (1LL << k)), cnt + 1);
        }
    };
    dfs((1LL << n) - 1, 0);
    return res;
}
*/