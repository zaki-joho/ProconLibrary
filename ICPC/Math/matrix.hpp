#include<bits/stdc++.h>
using namespace std;

using dbl = double;
using Mat = vector<vector<dbl>>;

const double EPS=1e-9;
bool isZero(dbl x){
    return abs(x)<=EPS;
}

Mat gaussianElimination(Mat mat){
    int m = mat.size(), n = mat[0].size();
    int row = 0;
    for(int j=0;j<n;j++){
        if(row==m) break;
        int tar = -1;
        dbl v = EPS;
        for(int i=row;i<m;i++){
            if(!isZero(mat[i][j]) && abs(v)<abs(mat[i][j])){
                tar = i;
                v = mat[i][j];
            }
        }
        if(tar==-1) continue;
        if(row!=tar) swap(mat[row],mat[tar]);
        for(int i= row+1;i<m;i++){
            if(!isZero(mat[i][j])){
                dbl r = mat[i][j]/mat[row][j];
                for(int k=j;k<n;k++){
                    mat[i][k]-=r*mat[row][k];
                }
            }
        }
        row++;
    }
    return mat;
}

int rank(Mat mat){
    int m = mat.size(), n = mat[0].size();
    mat = gaussianElimination(mat);
    int i=0,j=0;
    while(i<m && j<n){
        if(isZero(mat[i][j])) j++;
        else i++,j++;
    }
    return i;
}