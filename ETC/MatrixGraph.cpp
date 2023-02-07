#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t

/*
2099 AC Code
인접행렬에서 어떤 정점(u)에서 다른 정점(v)으로 정확히 K번 간선을 타고 이동할 수 있는 지 확인하려면 인접행렬을 K번 거듭제곱을 해주면 됩니다.
관련 문제
1. https://www.acmicpc.net/problem/2099
2. K-Path (번호 기억 안남;;)
3. https://www.acmicpc.net/problem/12850
4. 본대산책 시리즈
*/

using matrix = vector<vector<int>>;

matrix UnitMatrix(const int sz){
    matrix ret(sz, vector<int>(sz));
    for(int i = 0; i < sz; i++) ret[i][i] = 1;
    return ret;
}

matrix operator*(const matrix& a, const matrix& b){
    matrix ret(a.size(), vector<int>(b[0].size()));
    for(int i = 0; i < a.size(); i++){
        for(int j = 0; j < b.size(); j++){
            for(int k = 0; k < b[0].size(); k++){
                ret[i][k] += a[i][j] * b[j][k];
            }
        }
    }
    return ret;
}

matrix Pow(matrix& x, int n){
    matrix ret = UnitMatrix(x.size());
    while(n){
        if(n & 1) ret = ret *x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

int n,k,m;

int32_t main(){
    fastio;
    cin >> n >> k >> m;
    matrix x(n, vector<int>(n, 0));
    for(int i = 0; i < n; i++){
        int a,b; cin >> a >> b; --a,--b;
        x[i][b] = 1;
        x[i][a] = 1;
    }
    auto ret = Pow(x, k);
    while(m--){
        int a,b; cin >> a >> b; --a,--b;
        cout << (!ret[a][b] ? "life" : "death") << '\n';
    }
    return 0;
}
