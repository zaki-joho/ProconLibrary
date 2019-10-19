//verify http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A&lang=jp
#include<bits/stdc++.h>
using namespace std;
#include"../Graph/dijkstra.hpp"

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int V,E,r;
    cin>>V>>E>>r;
    Graph g(V);
    for(int i=0;i<E;i++){
        int s,t,d;
        cin>>s>>t>>d;
        g[s].push_back(Edge{s,t,d});
    }
    vector<cost_t> d;
    dijkstra(r,g,d);
    for(int i=0;i<V;i++){
        if(d[i]<INF) cout<<d[i]<<"\n";
        else cout<<"INF"<<"\n";
    }
    
    return 0;
}