// verify(http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A)
#include<bits/stdc++.h>
using namespace std;
#include"../Graph/dinic.hpp"

int main(){
    int V,E;
    cin>>V>>E;
    Dinic dinic(V);
    for(int i=0;i<E;i++){
        int u,v,c;
        cin>>u>>v>>c;
        dinic.add_edge(u,v,c);
    }
    cout<<dinic.run(0,V-1)<<endl;
    return 0;
}