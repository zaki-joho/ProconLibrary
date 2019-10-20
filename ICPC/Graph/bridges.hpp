#include"graph.hpp"

Edges bridgesDetection(Graph& g){
    int n = g.size();
    vector<int> pre(n,-1);
    vector<int> low(n);
    Edges res;
    int k=0;
    function<int(int,int)> dfs=[&](int v,int prev){
        low[v] = pre[v];
        for(auto& e:g[v]){
            if(e.to==prev) continue;
            if(pre[e.to]==-1){
                pre[e.to] = k++;
                low[v] = min(low[v], dfs(e.to,v));
                if(pre[v]<low[e.to]) res.push_back(e);
            }
            else low[v] = min(low[v], pre[e.to]);
        }
        return low[v];
    };
    for(int i=0;i<n;i++){
        if(pre[i]==-1){
            pre[i]=k++;
            dfs(i,-1);
        }
    }
    return res;
}