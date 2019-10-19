#include<bits/stdc++.h>
using namespace std;

struct Dinic{
    const int INF=1e9;
    struct Edge{int to,cap,rev;};
    int n;
    vector<vector<Edge>> g;
    vector<int> iter,level;

    Dinic(int n):n(n),g(n),level(n),iter(n){}

    void add_edge(int from,int to,int cap){
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

    int dfs(int v,int t,int f){
        if(v == t) return f;
        for(int&i = iter[v]; i < (int) g[v].size(); i++){
            Edge& e = g[v][i];
            if(e.cap>0 && level[v]<level[e.to]){
                int d = dfs(e.to, t, min(f,e.cap));
                if(d>0) {
                    e.cap-= d;
                    g[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int run(int s,int t){
        int ret = 0,f;
        while(bfs(s),level[t]>=0){
            fill(begin(iter),end(iter),0);
            while((f=dfs(s,t,INF))>0) ret += f;
        }
        return ret;
    }
};