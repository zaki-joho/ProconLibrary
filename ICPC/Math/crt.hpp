#include "../bits/stdc++.h"
using namespace std;
#include"extGcd.hpp"

// return (x,m) s.t. v=b0 (mod m0) and v=b1 (mod m1) <-> v=x (mod m)
// if such x don't exist, return (0,-1)
// O(log(m0)+log(m1))
// Note that the risk of overflow
pair<ll,ll> CRT(ll b0,ll m0,ll b1,ll m1){
    ll p,q;
    ll d = extGcd(m0,m1,p,q);
    if((b1-b0)%d!=0) return make_pair(ll(0),ll(-1));
    ll m = m0/d * m1;
    ll tmp = (b1-b0)/d * p % (m1/d);
    ll r = (b0 + m0 * tmp) % m;
    if(r<0) r = (r+m)%m;
    return make_pair(r,m);
}
