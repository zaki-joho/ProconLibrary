#include"graph.hpp"

const cost_t INF=1e9;
bool bellman_ford(int s,Graph& g,vector<cost_t>& d){
    int n = g.size();
    d.assign(n,INF);
    d[s] = 0;
    bool update=true;
    for(int i=0;update;i++){
        if(i==n){
            return false;
        }
        update=false;
        for(int i=0;i<n;i++){
            if(d[i]==INF) continue;
            for(auto &e:g[i]){
                cost_t tmp = d[i] + e.cost;
                if(tmp<d[e.to]){
                    d[e.to]=tmp;
                    update=true;
                }
            }
        }
    }
    return true;
}