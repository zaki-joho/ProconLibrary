#include"graph.hpp"

const cost_t INF=1e9;
void spfa(int s,Graph& g,vector<cost_t>& d){
    int n=g.size();
    d.assign(n,INF);
    vector<int> used(n);
    used[s]=true;
    d[s]=0;
    queue<int> que;
    que.push(s);
    while(!que.empty()){
        int v = que.front(); que.pop();
        used[v]=false;
        for(auto& e:g[v]){
            cost_t tmp = d[v]+e.cost;
            if(!used[e.to] && tmp<d[e.to]){
                que.push(e.to);
                used[e.to]=true;                
            }
            d[e.to]=min(d[e.to],tmp);
        }
    }
}