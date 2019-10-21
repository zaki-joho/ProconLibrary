// verify(http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A)
#include<bits/stdc++.h>
using namespace std;
#include"../Graph/ford_fullkerson.hpp"

int main(){
    int V,E;
    cin>>V>>E;
    FordFullkerson fk(V);
    for(int i=0;i<E;i++){
        int u,v,c;
        cin>>u>>v>>c;
        fk.add_edge(u,v,c);
    }
    cout<<fk.run(0,V-1)<<endl;
    return 0;
}