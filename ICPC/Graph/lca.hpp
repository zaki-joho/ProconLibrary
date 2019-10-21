#include"graph.hpp"

struct LCA{
    static const int LOGN=20;
    array<vector<int>,LOGN+1> par;
    vector<int> dep;
    void dfs(int v,int pre,Graph& g){
        for(auto& e:g[v]){
            if(e.to==pre) continue;
            par[0][e.to]=v;
            dep[e.to]=dep[v]+1;
            dfs(e.to,v,g);
        }
    }

    LCA(Graph& g,int root):dep(g.size()){
        int n=g.size();
        for(int i=0;i<=LOGN;i++) par[i].assign(n,-1);
        dep[root]=0;
        par[0][root]=root;
        dfs(root,-1,g);
        for(int i=0;i<LOGN;i++){
            for(int j=0;j<n;j++){
                par[i+1][j]=par[i][par[i][j]];
            }
        }
    }

    int query(int u,int v){
        if(dep[u]<dep[v]) swap(u,v);
        int d = dep[u]-dep[v];
        for(int i=LOGN;i>=0;i--){
            if((d>>i)&1){
                u = par[i][u];
                d-=(1<<i);
            }
        }
        if(u==v) return u;
        for(int i=LOGN;i>=0;i--){
            if(par[i][u]!=par[i][v]) u=par[i][u],v=par[i][v];
        }
        return par[0][u];
    }
};