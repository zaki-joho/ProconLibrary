
using ll=long long;

ll powm(ll x,ll k,ll mod){
    ll res=1;
    while(k){
        if(k&1) res=res*x%mod;
        x=x*x%mod;
        k>>=1;
    }
    return res;
}