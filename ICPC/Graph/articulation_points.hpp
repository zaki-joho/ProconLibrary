#include"graph.hpp"

vector<int> articulation_points(Graph& g){
    int n = g.size();
    vector<int> pre(n,-1);
    vector<int> low(n);
    vector<int> res;
    int k=0;
    function<int(int,int,int)> dfs=[&](int v,int prev,int org){
        low[v] = pre[v];
        bool isok=true;
        int cnt = 0;
        for(auto& e:g[v]){
            if(e.to==prev) continue;
            if(pre[e.to]==-1){
                pre[e.to] = k++;
                low[v] = min(low[v], dfs(e.to,v,org));
                isok = isok && low[e.to]<pre[v];
                cnt++;
            }
            else low[v] = min(low[v], pre[e.to]);
        }
        
        if(v==org){
            if(g[v].size()!=1 && cnt>1) res.push_back(v);
        }
        else if(!isok) res.push_back(v);
        return low[v];
    };
    // if connected -> dfs(0,-1,0);
    for(int i=0;i<n;i++){
        if(pre[i]==-1){
            pre[i]=k++;
            dfs(i,-1,i);
        }
    }
    return res;
}