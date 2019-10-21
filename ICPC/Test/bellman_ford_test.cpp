// verify (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B&lang=jp)
#include<bits/stdc++.h>
using namespace std;
#include"../Graph/bellman_ford.hpp"

int main(){
    int V,E,r;
    cin>>V>>E>>r;
    Graph g(V);
    for(int i=0;i<E;i++){
        int s,t,d;
        cin>>s>>t>>d;
        g[s].push_back(Edge(s,t,d));
    }
    vector<int> d;
    auto ret = bellman_ford(r,g,d);
    if(ret){
        for(int i=0;i<V;i++){
            if(d[i]==INF) cout<<"INF"<<endl;
            else cout<<d[i]<<endl;
        }
    }
    else{
        cout<<"NEGATIVE CYCLE"<<endl;
    }
    return 0;
}