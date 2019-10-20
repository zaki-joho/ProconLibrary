#include<bits/stdc++.h>
using namespace std;

using dbl = double;
using C = complex<dbl>;
using Poly = vector<C>;
const dbl PI = acos(-1);

void fft(Poly& f,C w){
    int n=f.size();
    if(n==1){
        return;
    }
    int k=n/2;
    Poly f0(k),f1(k);
    for(int i=0;i<k;i++) f0[i]=f[i*2];
    for(int i=0;i<k;i++) f1[i]=f[i*2+1];
    fft(f0,w*w);
    fft(f1,w*w);
    C pw = 1;
    for(int i=0;i<n;i++){
        f[i] = f0[i%k] + pw * f1[i%k];
        pw *= w;
    }
}

Poly evaluate(Poly f){
    int n=f.size();
    fft(f,polar(dbl(1),2*PI/n));
    return f;
}

Poly interpolate(Poly f){
    int n = f.size();
    fft(f,polar(dbl(1),-2*PI/n));
    for(auto &v:f) v/=n;
    return f;
}