#include"graph.hpp"

int scc(Graph &g,vector<int>& cmp){
    int n=g.size();
    vector<int> used(n);
    vector<int> ord(n,-1);
    int k=0;
    function<void(int)> dfs=[&](int v){
        if(used[v]) return;
        used[v]=true;
        for(auto& e:g[v]){
            dfs(e.to);
        }
        ord[k++]=v;
    };
    for(int i=0;i<n;i++){
        if(!used[i]) dfs(i);
    }
    vector<vector<int>> rg(n);
    for(int i=0;i<n;i++){
        for(auto& e:g[i]) rg[e.to].push_back(i);
    }
    k=0;
    cmp.assign(n,-1);
    function<void(int)> rdfs=[&](int v){
        if(cmp[v]!=-1) return;
        cmp[v]=k;
        for(auto to:rg[v]) rdfs(to);
    };
    for(int i=n-1;i>=0;i--){
        if(cmp[ord[i]]==-1) rdfs(ord[i]),k++;
    }
    return k;
}
