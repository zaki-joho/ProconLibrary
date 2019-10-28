#include<bits/stdc++.h>
using namespace std;
#include"../Math/matrix.hpp"

// edit EPS=1e-10
void AOJ_2171(){
    const type INF=1e9;
    int n,s,t;
    while(cin>>n>>s>>t,n){
        s--,t--;
        vector<int> q(n);
        for(int i=0;i<n;i++) cin>>q[i];
        Mat a(n,Vec(n));
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin>>a[i][j];
        for(int i=0;i<n;i++)for(int j=0;j<n;j++) if(i!=j && a[i][j]==0) a[i][j]=INF;
        
        Mat d=a;
        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
            }
        }
        
        const type EPS=1e-9;
        auto Eq=[&](type a,type b){
            return abs(a-b)<EPS;
        };

        if(Eq(d[s][t],INF)){
            cout<<"impossible"<<endl;
            continue;
        }

        Mat mat(n,Vec(n));
        Vec vec(n);
        for(int i=0;i<n;i++){
            if(i==t){
                mat[i][i]=1;
                vec[i]=0;
                continue;
            }
            int cnt=0;
            type sum=0;
            for(int j=0;j<n;j++){
                if(i==j) continue;
                if(Eq(a[i][j],INF)) continue;
                bool cango;
                if(q[i]==1) cango=Eq(d[i][t],a[i][j]+d[j][t]);
                else cango=(!Eq(a[i][j],INF));
                if(cango){
                    cnt++;
                    sum+=a[i][j];
                    mat[i][j]=-1;
                }
            }
            if(cnt==0) continue;
            vec[i]=sum/cnt;
            for(int j=0;j<n;j++) mat[i][j]/=cnt;
            mat[i][i]=1;
        }

        auto res=linearEq(mat,vec);
        cout<<setprecision(10)<<fixed;
        cout<<res[s]<<endl;
    }
    return;
}

// edit EPS=1e-4
// verify only linearEq existence
void AOJ_132(){
    int d;
    while(cin>>d,d){
        Vec v(d+3);
        for(int i=0;i<=d+2;i++) cin>>v[i];
        Mat mat(d+3,Vec(d+1));
        for(int i=0;i<=d+2;i++) mat[i][0]=1;
        for(int i=1;i<=d+2;i++) for(int j=1;j<=d;j++) mat[i][j]=pow(i,j);

        auto check=[](Mat mat,Vec vec){
            auto tmp=linearEq(mat,vec);
            return tmp.size();
        };
        for(int i=0;i<=d+2;i++){
            auto tmpMat=mat;
            auto tmpVec=v;
            tmpMat.erase(tmpMat.begin()+i);        
            tmpVec.erase(tmpVec.begin()+i);
            if(check(tmpMat,tmpVec)){
                cout<<i<<endl;
                break;
            }
        }
    }
    return;
}

void test_linearEq(){
    // AOJ_1328();    
    AOJ_2171();
}

int main(){
    test_linearEq();
    return 0;
}
