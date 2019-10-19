#include<bits/stdc++.h>
using namespace std;
#include"../Graph/min_cost_flow.hpp"

int main(){
    int V,E,F;
    cin>>V>>E>>F;
    MinCostFlow mcf(V);
    for(int i=0;i<E;i++){
        int u,v,c,d;
        cin>>u>>v>>c>>d;
        mcf.add_edge(u,v,c,d);
    }
    int ret = mcf.minCostFlow(0,V-1,F);
    cout<<ret<<endl;
    return 0;
}