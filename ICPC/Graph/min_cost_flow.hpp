#include<bits/stdc++.h>
using namespace std;

struct MinCostFlow{
    const int INF=1e9;
    struct Edge{int to,cap,cost,rev;};
    vector<vector<Edge>> g;
    vector<int> h,dist,prevv,preve;
    int n;

    MinCostFlow(int n):n(n),g(n),h(n),dist(n),prevv(n),preve(n){}

    void add_edge(int from,int to,int cap,int cost){
        g[from].push_back((Edge){to,cap,cost,(int)g[to].size()});
        g[to].push_back((Edge){from,0,-cost,(int)g[from].size()-1});
    }

    int minCostFlow(int s,int t,int f){
        int res = 0;
        while(f>0){
            using Item=pair<long long,int>;
            priority_queue<Item,vector<Item>,greater<>> que;
            fill(begin(dist),end(dist),INF);
            dist[s] = 0;
            que.push(Item(0,s));
            while(!que.empty()){
                auto tmp = que.top(); que.pop();
                int v = tmp.second;
                if(dist[v]<tmp.first) continue;
                for(int i=0;i<g[v].size();i++){
                    Edge& e=g[v][i];
                    int d = dist[v]+e.cost+h[v]-h[e.to];
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
            int d = f;
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