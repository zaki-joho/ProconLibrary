#include "../bits/stdc++.h"

class HLDecomposition
{
    int n, pos;
    std::vector<std::vector<int>> g;
    // vid:=HLD後のグラフでのid, head:=属するheavy path の head, sub:=子孫数
    // hvy:=heavy path 上の次の頂点, par:=parent, dep:=depth, inv:=vidの逆, type:=森用
    std::vector<int> vid, head, sub, hvy, par, dep, inv, type;

    void dfs(int cur)
    {
        for (auto nxt : g[cur])
        {
            if (nxt == par[cur])
                continue;
            par[nxt] = cur;
            dep[nxt] = dep[cur] + 1;
            dfs(nxt);
        }
        int ret = 0;
        for (auto u : g[cur])
        {
            if (u == par[cur])
                continue;
            sub[cur] += sub[u];
            if (ret < sub[u])
            {
                ret = sub[u];
                hvy[cur] = u;
            }
        }
    }

    void bfs(int r, int c)
    {
        std::queue<int> que({r});
        while (!que.empty())
        {
            int h = que.front();
            que.pop();
            for (int i = h; i != -1; i = hvy[i])
            {
                type[i] = c;
                vid[i] = pos++;
                inv[vid[i]] = i;
                head[i] = h;
                for (int j : g[i])
                    if (j != par[i] && j != hvy[i])
                        que.push(j);
            }
        }
    }

public:
    HLDecomposition() {}
    HLDecomposition(int sz) : n(sz), pos(0), g(n),
                              vid(n, -1), head(n), sub(n, 1), hvy(n, -1),
                              par(n, -1), dep(n, 0), inv(n), type(n) {}

    void add_edge(int u, int v)
    {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void build(std::vector<int> rs = std::vector<int>(1, 0))
    {
        int c = 0;
        for (int r : rs)
        {
            dfs(r);
            bfs(r, c++);
        }
    }

    // f(l, r) := [l, r] に対する演算
    void for_each_vertex(int u, int v, const std::function<void(int, int)> &f)
    {
        while (true)
        {
            if (vid[u] > vid[v])
                std::swap(u, v);
            f(std::max(vid[head[v]], vid[u]), vid[v]);
            if (head[u] == head[v])
                break;
            v = par[head[v]];
        }
    }

    // f(l, r) := [l, r] に対する演算
    void for_each_edge(int u, int v, const std::function<void(int, int)> &f)
    {
        while (true)
        {
            if (vid[u] > vid[v])
                std::swap(u, v);
            if (head[u] == head[v])
            {
                if (u != v)
                    f(vid[u] + 1, vid[v]);
                break;
            }
            f(vid[head[v]], vid[v]);
            v = par[head[v]];
        }
    }

    int lca(int u, int v)
    {
        while (true)
        {
            if (vid[u] > vid[v])
                std::swap(u, v);
            if (head[u] == head[v])
                return u;
            v = par[head[v]];
        }
    }

    int distance(int u, int v)
    {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};
