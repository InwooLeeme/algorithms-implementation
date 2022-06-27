#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t


int LIS(int n){ // get LIS size using lower_bound
    int n; cin >> n;
    vector<int> LIS;
    for(int i = 0; i < n; i++){
        int t; cin >> t;
        if(LIS.empty() or LIS.back() < t) LIS.push_back(t);
        else *lower_bound(LIS.begin(), LIS.end(), t) = t;
    }
    return LIS.size();
}