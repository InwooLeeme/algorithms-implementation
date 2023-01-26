#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int int_fast64_t
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

/*
https://www.acmicpc.net/problem/12082
12082 AC Code
Find BipartiteGraph
*/

string Sol(){
    int m,idx = 0; cin >> m; cin.ignore();
    unordered_map<string ,int> M;
    vector<vector<int>> adj(m << 1 + 1);
    while(m--){
        string a,b; cin >> a >> b;
        if(!M.count(a)) M[a] = idx++;
        if(!M.count(b)) M[b] = idx++;
        adj[M[a]].push_back(M[b]);
        adj[M[b]].push_back(M[a]);
    }
    bool flag = 0;
    vector<int> color(2222, 0);
    function<void(int)> DFS = [&](int cur) -> void{
        for(auto nxt : adj[cur]){
            if(!color[nxt]){
                color[nxt] = 3 - color[cur];
                DFS(nxt);
            }
            if(color[nxt] == color[cur]){
                flag = 1;
                return;
            }
        }
    };  
    for(int i = 0; i < idx; i++) DFS(i);
    return (flag ? "No" : "Yes");
}

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    for(int tc = 1; tc <= T; tc++){
        cout << "Case #" << tc << ": " << Sol() << "\n";
    }
}   
