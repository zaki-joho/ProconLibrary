#include<bits/stdc++.h>
using namespace std;
const int MAX_V = 100;

using Mask=bitset<MAX_V>;
using BGraph=vector<Mask>;
vector<int> maximum_independent_set(BGraph& g,Mask usable){
    int n = g.size();
    vector<int> res;
    for(int i=0;i<n;i++){
        if(!usable[i]) continue;
        int cnt = (usable & g[i]).count();
        if(cnt<=1){
            res.push_back(i);
            usable &= ~g[i];
            usable[i]=false;
        }
    }
    int v=-1;
    for(int i=0;i<n;i++){
        if(usable[i]){
            v=i;
            break;
        }
    }
    if(v==-1) return res;
    usable[v] = false;
    auto ret0 = maximum_independent_set(g,usable);
    usable &= ~g[v];
    auto ret1 = maximum_independent_set(g,usable);
    ret1.push_back(v);
    if(ret0.size()<ret1.size()) res.insert(end(res),begin(ret1),end(ret1));
    else res.insert(end(res),begin(ret0),end(ret0));
    return res;
}