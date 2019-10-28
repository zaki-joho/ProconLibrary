// verify https://yukicoder.me/problems/no/187
#include<bits/stdc++.h>
using namespace std;
#include"../Math/garnerCRT.hpp"

// modify ll -> __int128
int main(){
    int n;
    cin>>n;
    vector<ll> x(n),y(n);
    for(int i=0;i<n;i++) cin>>x[i]>>y[i];
    
    map<ll,pair<int,ll>> mcb;
    for(int i=0;i<n;i++){
        map<ll,int> mp;
        ll v=y[i];
        for(ll j=2;j*j<=v;j++){
            if(v%j==0){
                int cnt=0;
                while(v%j==0) cnt++,v/=j;
                mp[j]=cnt;
            }
        }
        if(v>1){
            mp[v]=1;
        }
        for(auto& p:mp){
            if(mcb.count(p.first)){
                ll prem = 1;
                for(int j=0;j<mcb[p.first].first;j++) prem=prem*p.first;
                ll nowm = 1;
                for(int j=0;j<p.second;j++) nowm=nowm*p.first;
                ll mod = min(prem,nowm);
                if(mcb[p.first].second%mod!=x[i]%mod){
                    cout<<-1<<endl;
                    return 0;
                }
                if(prem<nowm) mcb[p.first]={max(p.second,mcb[p.first].first),x[i]%nowm};
                else mcb[p.first]={max(p.second,mcb[p.first].first),mcb[p.first].second};
            }
            else{
                ll tmp=1;
                for(int j=0;j<p.second;j++) tmp=tmp*p.first;
                mcb[p.first]={p.second,x[i]%tmp};
            }
        }
    }

    vector<ll> b,m;
    for(auto& e:mcb){
        b.push_back(e.second.second);
        ll tmp=1;
        for(int i=0;i<e.second.first;i++) tmp*=e.first;
        m.push_back(tmp);
        b.back()%=m.back();
    }
    if(all_of(x.begin(),x.end(),[](ll v){return v==0;})){
        ll res = 1;
        for(auto v:m) res=res*v%MOD;
        cout<<res<<endl;
        return 0;
    }
    ll ret = crt(b,m);
    cout<<crt(b,m)<<endl;
    return 0;
}