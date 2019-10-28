#include<bits/stdc++.h>
using namespace std;

using dbl = double;
using C = complex<dbl>;
using Poly = vector<C>;
const dbl PI = acos(-1);

Poly fft(Poly f,C w){
    int n = f.size();
    for (int m = n; m >= 2; m >>= 1){
        int mh = m >> 1;
        C wt = 1;
        for (int i = 0; i < mh; i++){
            for (int j = i; j < n; j += m){
                C x = f[j] - f[j + mh];
                f[j] = f[j] + f[j + mh];
                f[j + mh] = wt * x;
            }
            wt *= w;
        }
        w *= w;
    }
    int i = 0;
    for (int j = 1; j < n - 1; j++){
        for (int k = n >> 1; k > (i ^= k); k >>= 1) ;
        if (j < i) swap(f[i], f[j]);
    }
    return f;
}

Poly evaluate(Poly f){
    int n=f.size();
    f = fft(f,polar(dbl(1),2*PI/n));
    return f;
}

Poly interpolate(Poly f){
    int n = f.size();
    f = fft(f,polar(dbl(1),-2*PI/n));
    for(auto &v:f) v/=n;
    return f;
}

Poly convolution(Poly a,Poly b){
    int tar=(int)(a.size()+b.size())-1;
    int sz=1;
    while(sz<tar) sz*=2;
    a.resize(sz);
    b.resize(sz);
    a = evaluate(a),b = evaluate(b);
    for(int i=0;i<sz;i++) a[i] *= b[i];
    a = interpolate(a);
    return a;
}