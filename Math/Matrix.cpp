#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

using matrix = vector<vector<int>>;

struct Matrix{
    int MOD;
    Matrix(int mod):
        MOD(mod){}
    // make UnitMatrix (n X n)
    matrix UnitMatrix(int sz){ 
        matrix ret(sz, vector<int>(sz, 0));
        for(int i = 0; i < sz; i++) matrix[i][i] = 1;
        return ret;
    }
    // multiply each Matrix
    matrix operator *(matrix& a,matrix& b){
        matrix ret(a.size(), vector<int>(b[0].size()));
        for(int i = 0; i < a.size(); i++){
            for(int j = 0; j < b.size(); j++){
                for(int k = 0; k < b[0].size(); k++){
                    ret[i][k] = (ret[i][k] + a[i][j] * b[j][k]) % MOD;
                }
            }
        }
        return ret;
    }
    // pow matrix using divide and conquer
    _pow(matrix& x,int n){
        matrix ret = UnitMatrix(x.size());
        while(n){
            if(n & 1) ret = ret * x;
            x = x * x;
            n >>= 1;
        }
        return ret;
    }
};

int32_t main(){
    fastio;
}