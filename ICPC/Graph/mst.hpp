#include"graph.hpp"

cost_t mst(Graph& g){
    int n=g.size();
    cost_t res=0;
    using Item=pair<cost_t,int>;
    priority_queue<Item,vector<Item>,greater<>> que;
    que.push(Item(0,0));
    vector<int> used(n);
    while(!que.empty()){
        auto tmp=que.top(); que.pop();
        int v=tmp.second;
        if(used[v]) continue;
        used[v]=true;
        res+=tmp.first;
        for(auto &e:g[v]){
            if(!used[e.to]) que.push(Item(e.cost,e.to));
        }
    }
    return res;
}