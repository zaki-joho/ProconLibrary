#include "../bits/stdc++.h"
using namespace std;

struct MinCostFlow{
    using flow_t = int;
    using cost_t = int;
    const int INF=1e9;
    struct Edge{int to; flow_t cap; cost_t cost,rev;};
    vector<vector<Edge>> g;
    vector<cost_t> h,dist;
    vector<int> prevv,preve;
    int n;

    MinCostFlow(int n):n(n),g(n),h(n),dist(n),prevv(n),preve(n){}

    void add_edge(int from,int to,flow_t cap,cost_t cost){
        g[from].push_back(Edge{to,cap,cost,(int)g[to].size()});
        g[to].push_back(Edge{from,0,-cost,(int)g[from].size()-1});
    }

    cost_t run(int s,int t,flow_t f){
        cost_t res = 0;
        while(f>0){
            using Item=pair<cost_t,int>;
            priority_queue<Item,vector<Item>,greater<>> que;
            fill(begin(dist),end(dist),INF);
            dist[s] = 0;
            que.push(Item(0,s));
            while(!que.empty()){
                auto tmp = que.top(); que.pop();
                int v = tmp.second;
                if(dist[v]<tmp.first) continue;
                for(int i=0;i<(int)g[v].size();i++){
                    Edge& e=g[v][i];
                    cost_t d = dist[v]+e.cost+h[v]-h[e.to];
                    if(e.cap>0 && dist[e.to]>d){
                        dist[e.to] = d;
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.push(Item(dist[e.to],e.to));
                    }
                }
            }

            if(dist[t]==INF) return -1;
            for(int i=0;i<n;i++) h[i]+=dist[i];
            flow_t d = f;
            for(int v=t;v!=s;v=prevv[v]){
                d=min(d,g[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d*h[t];
            for(int v=t;v!=s;v=prevv[v]){
                Edge& e = g[prevv[v]][preve[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return res;
    }
};