#include<bits/stdc++.h>
using namespace std;

#include"../Math/fft.hpp"
const int MAX_N = 1<<18;

int main(){
    int N;
    cin>>N;
    Poly A(MAX_N),B(MAX_N);
    for(int i=0;i<N;i++){
        int a,b;
        cin>>a>>b;
        A[i+1]=C(a,0),B[i+1]=C(b,0);
    }
    
    C w = polar(1., 2*PI/MAX_N);
    A=evaluate(A),B=evaluate(B);
    Poly C(MAX_N);
    for(int i=0;i<MAX_N;i++){
        C[i]=A[i]*B[i];        
    }
    C=interpolate(C);
    for(int i=1;i<=2*N;i++){
        cout<<(int)(round(real(C[i])))<<endl;
    }
    return 0;
}