#include "../bits/stdc++.h"

// 最大流(Dinic)
// O(EV^2) (<=> Ford : O(FE))
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3381606
class Dinic
{
    using type = int;
    const int INF = 1e9;
    struct Edge
    {
        type to, cap, rev;
        Edge(int _t, int _c, int _r) : to(_t), cap(_c), rev(_r) {}
    };

    using Graph = std::vector<std::vector<Edge>>;
    int V;
    Graph G;
    std::vector<int> level;
    std::vector<int> iter;

    void bfs(int s)
    {
        fill(level.begin(), level.end(), -1);
        std::queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty())
        {
            int v = que.front();
            que.pop();
            for (const auto &e : G[v])
            {
                if (e.cap > 0 && level[e.to] < 0)
                {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }
    type dfs(int v, int t, type f)
    {
        if (v == t)
            return f;
        for (int &i = iter[v]; i < (int)G[v].size(); i++)
        {
            Edge &e = G[v][i];
            if (e.cap > 0 && level[v] < level[e.to])
            {
                type d = dfs(e.to, t, std::min(f, e.cap));
                if (d > 0)
                {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

  public:
    Dinic(int _v) : V(_v), G(_v), level(_v), iter(_v) {}
    void add(int from, int to, int cap)
    {
        G[from].push_back(Edge{to, cap, (int)G[to].size()});
        G[to].push_back(Edge{from, 0, (int)G[from].size() - 1});
    }
    type maxFlow(int s, int t)
    {
        type ret = 0;
        while (true)
        {
            bfs(s);
            if (level[t] < 0)
                return ret;
            fill(iter.begin(), iter.end(), 0);
            type f;
            while ((f = dfs(s, t, INF)) > 0)
            {
                ret += f;
            }
        }
    }
};

/*
https://ei1333.github.io/algorithm/dinic.html
http://yosupo.hatenablog.com/entry/2015/03/31/134336
燃やす埋める
以下のような制約問題は最小カットに帰着できる
- 各頂点に {0, 1} を割り当て
- 頂点 x_i に 0, 頂点 y_i に 1 を割り当てたとき, z_i の損失
- 損失の和の最小値を求めよ

-> x_i から y_i に z_i の辺を張って最大流(=最小カット)が求める値に等しい

x_i = 0, z_i 損失 -> (x_i, T, z_i)
x_i = 1, z_i 損失 -> (S, x_i, z_i) etc...
*/
