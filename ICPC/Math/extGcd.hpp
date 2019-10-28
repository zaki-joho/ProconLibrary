using ll=long long;

ll extGcd(ll a,ll b,ll& p,ll &q){
    if(b==0) {p=1; q=0; return a;}
    ll d = extGcd(b,a%b,q,p);
    q -= a/b * p;
    return d;
}