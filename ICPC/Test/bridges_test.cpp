// verified(http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B)
#include<bits/stdc++.h>
using namespace std;

#include"../Graph/bridges.hpp"

int main(){
    int V,E;
    cin>>V>>E;
    Graph g(V);
    for(int i=0;i<E;i++){
        int s,t;
        cin>>s>>t;
        g[s].push_back(Edge(s,t,0));
        g[t].push_back(Edge(t,s,0));
    }
    auto res = bridgesDetection(g);
    auto cmp=[&](Edge lhs,Edge rhs){
        auto mP=[&](Edge e){
            return make_pair(min(e.from,e.to),max(e.from,e.to));
        };
        auto lP=mP(lhs),rP=mP(rhs);
        return lP<rP;
    };
    sort(res.begin(),res.end(),cmp);
    for(auto &e:res){
        cout<<min(e.from,e.to)<<" "<<max(e.from,e.to)<<endl;
    }
    return 0;
}