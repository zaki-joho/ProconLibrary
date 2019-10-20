// verified (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C)
#include<bits/stdc++.h>
using namespace std;
#include"../Graph/lca.hpp"

int main(){
    int n;
    cin>>n;
    Graph g(n);
    for(int i=0;i<n;i++){
        int k;
        cin>>k;
        while(k--){
            int v; cin>>v;
            g[i].push_back(Edge(i,v,0));
            g[v].push_back(Edge(v,i,0));
        }
    }
    LCA lca(g,0);
    int q;
    cin>>q;
    while(q--){
        int u,v;
        cin>>u>>v;
        cout<<lca.query(u,v)<<endl;
    }
    return 0;
}