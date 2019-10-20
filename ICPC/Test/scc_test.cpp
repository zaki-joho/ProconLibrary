#include<bits/stdc++.h>
using namespace std;

#include"../Graph/scc.hpp"

int main(){
    int V,E;
    cin>>V>>E;
    Graph g(V);
    for(int i=0;i<E;i++){
        int s,t;
        cin>>s>>t;
        g[s].push_back(Edge(s,t,0));
    }
    vector<int> cmp;
    int k=scc(g,cmp);
    assert(k==(*max_element(cmp.begin(),cmp.end())+1));
    int Q;
    cin>>Q;
    for(int i=0;i<Q;i++){
        int u,v;
        cin>>u>>v;
        cout<<(cmp[u]==cmp[v])<<endl;
    }
    return 0;
}