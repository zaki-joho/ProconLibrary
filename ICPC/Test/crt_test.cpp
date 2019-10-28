// verify https://yukicoder.me/problems/no/186
#include<bits/stdc++.h>
using namespace std;
#include"../Math/crt.hpp"

// modify ll -> __int128
int main(){
    vector<ll> x(3),y(3);
    for(int i=0;i<3;i++) cin>>x[i]>>y[i];
    auto ret = CRT(x[0],y[0],x[1],y[1]);
    if(ret.second==-1){
        cout<<-1<<endl;
        return 0;
    }    
    ret = CRT(ret.first,ret.second,x[2],y[2]);
    if(ret.second==-1){
        cout<<-1<<endl;
        return 0;
    }
    cout<<(ret.first==0 ? ret.second : ret.first)<<endl;
    return 0;
}