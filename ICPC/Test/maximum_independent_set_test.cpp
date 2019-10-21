// verified (https://code-thanks-festival-2017-open.contest.atcoder.jp/tasks/code_thanks_festival_2017_g)
#include<bits/stdc++.h>
using namespace std;
#include"../Graph/maximum_independent_set.hpp"

int main(){
    int N,M;
    cin>>N>>M;
    BGraph g(N);
    for(int i=0;i<M;i++){
        int a,b;
        cin>>a>>b;
        a--,b--;
        g[a][b]=g[b][a]=true;
    }
    Mask mask;
    for(int i=0;i<N;i++) mask[i]=true;
    cout<<maximum_independent_set(g,mask).size()<<endl;
    return 0;
}