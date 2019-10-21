#include<bits/stdc++.h>
using namespace std;

#include"../Graph/articulation_points.hpp"

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
    auto res= articulation_points(g);
    sort(res.begin(),res.end());
    for(auto v:res){
        cout<<v<<endl;
    }
    return 0;
}