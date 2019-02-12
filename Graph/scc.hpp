// verified: https://codeforces.com/contest/1100/submission/49830281
// O(|V| + |E|)
class Scc
{
    using Graph = vector<vector<int>>;
    int V, K;
    Graph G, rG;
    vector<int> vs;
    vector<bool> used;
    vector<int> cmp;
    void dfs(int cur)
    {
        used[cur] = true;
        for (const auto &v : G[cur])
        {
            if (!used[v])
                dfs(v);
        }
        vs.push_back(cur);
    }
    void rdfs(int cur, int k)
    {
        used[cur] = true;
        cmp[cur] = k;
        for (const auto &v : rG[cur])
        {
            if (!used[v])
                rdfs(v, k);
        }
    }

  public:
    Scc(int _V) : V(_V), G(_V), rG(_V), used(_V, false), cmp(_V) {}
    void add_edge(int from, int to)
    {
        G[from].push_back(to);
        rG[to].push_back(from);
    }
    // SCCした後の頂点の対応関係(xor頂点数)を取得する
    vector<int> scc()
    {
        for (int i = 0; i < V; i++)
            used[i] = false;
        vs.clear();
        for (int v = 0; v < V; v++)
        {
            if (!used[v])
                dfs(v);
        }
        for (int i = 0; i < V; i++)
            used[i] = false;
        int k = 0;
        for (int i = (int)vs.size() - 1; i >= 0; i--)
        {
            if (!used[vs[i]])
                rdfs(vs[i], k++);
        }
        // 頂点数
        K = k;
        // cmp[i] := 頂点i がSCC後に属する強連結成分番号
        return cmp;
    }
    // 強連結成分を潰した後のグラフを得る
    Graph buildGraph()
    {
        scc();
        vector<set<int>> s(K);
        Graph ret(K);
        for (int v = 0; v < V; v++)
        {
            for (const auto to : G[v])
            {
                s[cmp[v]].insert(cmp[to]);
            }
        }
        for (int i = 0; i < K; i++)
        {
            for (auto j : s[i])
            {
                if (i != j)
                    ret[i].push_back(j);
            }
        }
        return ret;
    }
};
