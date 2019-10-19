// verified (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A)
#include<bits/stdc++.h>
using namespace std;
#include"../Graph/mst.cpp"

int main(){
    int V,E;
    cin>>V>>E;
    Graph g(V);
    for(int i=0;i<E;i++){
        int s,t,w;
        cin>>s>>t>>w;
        g[s].push_back(Edge(s,t,w));
        g[t].push_back(Edge(t,s,w));
    }
    cout<<mst(g)<<endl;
    return 0;
}
