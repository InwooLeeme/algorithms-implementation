#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

// 1D prefix sum : 0 - indexed base
const int sz = 10000;
int v[sz + 1],pSum[sz + 1];

// 2D prefix sum : 0 - indexed base



int32_t main(){
    int n; cin >> n;
    for(int i = 0; i < n; i++) cin >> v[i];
    // make prefix sum : 0- indexed base
    pSum[0] = v[0];
    for(int i = 1; i < n; i++) pSum[i] = pSum[i - 1] + v[i];
}