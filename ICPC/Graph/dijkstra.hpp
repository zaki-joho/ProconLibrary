#include"graph.hpp"

const cost_t INF=1e9+9; // must edit this
void dijkstra(int s,Graph& g,vector<cost_t>& d){
    int n=g.size();
    d.assign(n,INF);
    d[s]=0;
    using Item=pair<cost_t,int>;
    priority_queue<Item,vector<Item>,greater<Item>> que;
    que.push(Item(0,s));
    while(!que.empty()){
        auto tmp=que.top(); que.pop();
        int v=tmp.second;
        if(d[v]<tmp.first) continue;
        for(auto &e:g[v]){
            if(d[v]+e.cost<d[e.to]){
                d[e.to]=d[v]+e.cost;
                que.push(Item(d[e.to],e.to));
            }
        }
    }
}