#include<bits/stdc++.h>
using namespace std;

#include"../Math/fft.hpp"

int main(){
    int N;
    cin>>N;
    Poly A(N+1),B(N+1);
    for(int i=0;i<N;i++){
        int a,b;
        cin>>a>>b;
        A[i+1]=C(a,0),B[i+1]=C(b,0);
    }
    
    auto C = convolution(A,B);
    for(int i=1;i<=2*N;i++){
        cout<<(int)(round(real(C[i])))<<endl;
    }
    return 0;
}