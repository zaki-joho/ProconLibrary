#include<bits/stdc++.h>
using namespace std;

#include"../Math/lagrangeInterpolation.hpp"

int main(){
    int N;
    cin>>N;
    vector<ll> A(N+1);
    for(int i=0;i<=N;i++) cin>>A[i];

    ll T;
    cin>>T;

    cout<<LagrangeInterpolation(A,T)<<endl;
    
    return 0;
}