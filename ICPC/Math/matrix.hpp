#include "../bits/stdc++.h"
using namespace std;

using type = double;
using Vec = vector<type>;
using Mat = vector<Vec>;

const double EPS=1e-10;
bool isZero(type x){
    return abs(x)<=EPS;
}

// sweep mat[i][j] 0<=i<m && 0<=j<c(default c=n)
// return Vec{j| i,j s.t. minj mat[i][j]!=0}
vector<int> sweep(Mat& mat,int c=-1){
    if(c==-1) c=mat[0].size();
    int m = mat.size(),n=mat[0].size();
    int row = 0;
    vector<int> res;
    for(int j=0;j<c;j++){
        if(row==m) break;
        int tar = -1;
        type v = 0;
        for(int i=row;i<m;i++){
            if(!isZero(mat[i][j]) && abs(v)<abs(mat[i][j])){
                tar = i;
                v = mat[i][j];
            }
        }
        if(tar==-1) continue;
        if(row!=tar) swap(mat[row],mat[tar]);
        for(int i=0;i<m;i++){
            if(i==row) continue;
            if(!isZero(mat[i][j])){
                type r = mat[i][j]/mat[row][j];
                for(int k=j;k<n;k++){
                    mat[i][k]-=r*mat[row][k];
                }
            }
        }
        res.push_back(j);
        row++;
    }
    return res;
}

type det(Mat mat){
    sweep(mat);
    type res=1;
    int sz=mat.size();
    for(int i=0;i<sz;i++){
        if(isZero(mat[i][i])) return type(0);
        res*=mat[i][i];
    }
    return res;
}


int rank(Mat mat){
    int m = mat.size(), n = mat[0].size();
    return sweep(mat).size();
}

// return an answer of [mat*x=vec]
Vec linearEq(Mat mat,Vec vec){
    int m =mat.size(),n=mat[0].size();
    for(int i=0;i<mat.size();i++) mat[i].push_back(vec[i]);
    auto ids=sweep(mat);
    if(ids.back()==n) return {};
    Vec res(n);
    for(int i=0;i<ids.size();i++) res[ids[i]]=mat[i][n]/mat[i][ids[i]];
    return res;
}

// return kernel of mat i.e. basis of {vec|mat*vec==0}
vector<Vec> kernel(Mat mat){
    int h=mat.size(),w=mat[0].size();
    Mat tmp(w,Vec(h+w));
    for(int i=0;i<h;i++) for(int j=0;j<w;j++) tmp[j][i]=mat[i][j];
    for(int i=0;i<w;i++) tmp[i][h+i]=1;
    int r = sweep(tmp,h).size();
    vector<Vec> res;
    for(int i=r;i<w;i++) res.emplace_back(tmp[i].begin()+h,tmp[i].end());
    return res;
}