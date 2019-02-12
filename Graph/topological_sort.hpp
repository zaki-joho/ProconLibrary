// add edge していって　topologicalSort() でソート済みの列を返す
// O(N)
// verified: https://atcoder.jp/contests/nikkei2019-qual/submissions/4246223
class TopologicalSort
{
    using Graph = vector<vector<int>>;
    // 頂点数
    int V;
    vector<vector<int>> G;
    void dfs(int v, vector<int> &res, vector<int> &used)
    {
        used[v] = 1;
        for (auto to : G[v])
            if (used[to] == 0)
            {
                dfs(to, res, used);
            }
        res.push_back(v);
    }

  public:
    TopologicalSort(int _v) : V(_v), G(_v) {}
    void addEdge(int a, int b)
    {
        assert(0 <= a && a < V);
        assert(0 <= b && b < V);
        G[a].push_back(b);
    }
    vector<int> topologicalSort()
    {
        vector<int> ide(V);
        for (int i = 0; i < V; i++)
        {
            for (auto to : G[i])
            {
                ide[to]++;
            }
        }
        vector<int> res;
        vector<int> used(V);
        for (int i = V - 1; i >= 0; i--)
        {
            if (ide[i] == 0)
            {
                dfs(i, res, used);
            }
        }
        if (res.size() == 0)
            res = {-1};
        reverse(res.begin(), res.end());
        return res;
    }
};
