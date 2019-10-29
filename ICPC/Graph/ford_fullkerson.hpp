#include "../bits/stdc++.h"
using namespace std;

struct FordFullkerson{
    using flow_t = int;
    struct Edge{int to; flow_t cap; int rev;};
    const flow_t INF=1e9;
    vector<vector<Edge>> g;
    vector<int> used;

    FordFullkerson(int n):g(n),used(n){}

    void add_edge(int from,int to,flow_t cap){
        g[from].push_back(Edge{to,cap,(int)g[to].size()});
        g[to].push_back(Edge{from,0,(int)g[from].size()-1});
    }

    flow_t dfs(int v,int t,flow_t f){
        if(v == t) return f;
        used[v]=true;
        for(auto& e:g[v]){
            if(used[e.to] || e.cap <= 0) continue;
            flow_t d = dfs(e.to, t, min(f,e.cap));
            if(d > 0){
                e.cap -= d;
                g[e.to][e.rev].cap += d;
                return d;
            }
        }
        return 0;
    }

    flow_t run(int s,int t){
        flow_t flow=0,f;
        while(true){
            fill(used.begin(),used.end(),false);
            f = dfs(s,t,INF);
            if(f == 0) return flow;
            flow += f;
        }
    }
};