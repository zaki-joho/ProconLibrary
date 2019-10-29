#include "../bits/stdc++.h"
using namespace std;

struct Dinic{
    using flow_t = int;
    const flow_t INF = 1e9;
    struct Edge{int to; flow_t cap; int rev;};
    int n;
    vector<vector<Edge>> g;
    vector<int> iter,level;

    Dinic(int n):n(n),g(n),level(n),iter(n){}

    void add_edge(int from,int to,flow_t cap){
        g[from].push_back(Edge{to,cap,(int)g[to].size()});
        g[to].push_back(Edge{from,0,(int)g[from].size()});
    }

    void bfs(int s){
        fill(begin(level),end(level),-1);
        queue<int> que;
        level[s] = 0; que.push(s);
        while(!que.empty()){
            int v = que.front(); que.pop();
            for(auto& e:g[v]){
                if(e.cap>0 && level[e.to]<0){
                    level[e.to]=level[v]+1;
                    que.push(e.to);
                }
            }
        }
    }

    flow_t dfs(int v,int t,flow_t f){
        if(v == t) return f;
        for(int&i = iter[v]; i < (int) g[v].size(); i++){
            Edge& e = g[v][i];
            if(e.cap>0 && level[v]<level[e.to]){
                flow_t d = dfs(e.to, t, min(f,e.cap));
                if(d>0) {
                    e.cap-= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    flow_t run(int s,int t){
        flow_t ret = 0,f;
        while(bfs(s),level[t]>=0){
            fill(begin(iter),end(iter),0);
            while((f=dfs(s,t,INF))>0) ret += f;
        }
        return ret;
    }
};