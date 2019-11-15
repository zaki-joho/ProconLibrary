#include<bits/stdc++.h>
using namespace std;

using ll=long long;
const ll MOD=1e9+7;
ll powm(ll x,ll k){
    ll res=1;
    while(k){
        if(k&1) res=res*x%MOD;
        x=x*x%MOD;
        k>>=1;
    }
    return res;
}
ll modInv(ll x){
    return powm(x,MOD-2);
}

ll LagrangeInterpolation(vector<ll> P,ll x){
    int N=P.size()-1;
    vector<ll> Q(N+2);
    Q[0]=1;
    for(int i=0;i<N;i++) Q[i+1]=Q[i]*(x-i)%MOD;
    
    vector<ll> R(N+2);
    R[N+1]=1;
    for(int i=N;i>=0;i--) R[i]=R[i+1]*(x-i)%MOD;

    ll factN=1;
    for(int i=1;i<=N;i++) factN=factN*i%MOD;
    vector<ll> factInv(N+1);
    factInv[N]=modInv(factN);
    for(int i=N-1;i>=0;i--) factInv[i]=factInv[i+1]*(i+1)%MOD;

    ll res=0;
    for(int i=0;i<=N;i++){
        ll q=Q[i]*R[i+1]%MOD;
        ll p=factInv[i]*factInv[N-i]%MOD;
        ll tmp=p*q%MOD*P[i]%MOD;
        if((N-i)&1) res-=tmp;
        else res+=tmp;
    }
    return (res%MOD+MOD)%MOD;
}