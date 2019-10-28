#include<bits/stdc++.h>
#include"extGcd.hpp"
using namespace std;

using ll=long long;
const ll MOD=1e9+7;

// Note that mod may not be prime.
ll modInv(ll a,ll mod){
    long long x,y;
    extGcd(a,mod,x,y);
    return (x%mod+mod)%mod;
}

// all m must be coprime each other.
// O(K^2), where K is size of b and m
// return 
ll crt(vector<ll> b,vector<ll> m){
    int k=b.size();
    vector<ll> t(k);
    ll r;
    auto calc=[&](int end,ll mod){
        ll sum = 0;
        r=1;
        for(int i=0;i<end;i++){
            sum = (sum + r*t[i])%mod;
            r = r * m[i] % mod;
        }
        return sum;
    };
    for(int i=0;i<k;i++){
        t[i] = (b[i]-calc(i,m[i]))*modInv(r,m[i])%m[i];
        t[i] = (t[i]+m[i])%m[i];
    }
    return (calc(k,MOD)+MOD)%MOD;
}