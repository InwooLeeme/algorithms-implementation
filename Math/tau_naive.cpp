#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

/* 
N의 약수를 벡터에 저장
 */
vector<int> tau_naive(int x){
    vector<int> ret;
    for(int i = 1; i * i <= x; i++){
        if(x % i == 0){
            ret.push_back(i);
            ret.push_back(x / i);
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}

int32_t main(){
    fastio;
    int n; cin >> n;
    auto tau = tau_naive(n);
}