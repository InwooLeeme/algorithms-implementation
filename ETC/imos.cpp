#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t

/*
imos법 (누적합 확장)
BOJ 28018 AC Code
https://www.acmicpc.net/problem/28018
ref : https://driip.me/65d9b58c-bf02-44bf-8fba-54d394ed21e0
ref : https://daruiniji.tistory.com/65
입장시간 + 1, 퇴장시간 + 1에 -1
*/

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n,m; cin >> n;
    vector<int> v(1'000'011);
    for(int i = 0; i < n; i++){
        int s,e; cin >> s >> e;
        v[s]++,v[e + 1]--;
    }
    for(int i = 1; i < v.size(); i++) v[i] += v[i - 1];
    cin >> m;
    while(m--){
        int t; cin >> t;
        cout << v[t] << "\n";
    }
    return 0;
}
