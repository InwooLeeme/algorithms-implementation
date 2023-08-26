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

const int PRECISION = 0;

/*
Get Dist in Tree using LCA
problem URL : https://www.acmicpc.net/problem/7742
*/

/* 1 - indexed base */
struct LCA{
    using pii = pair<int, int>;
	int n;
	vector<vector<int>> par;
	vector<vector<pii>> adj;
	vector<int> depth,dist;
	vector<bool> vist;
	
	LCA(int n = 0):
		n(n),adj(n + 1),depth(n + 1),vist(n + 1),dist(n + 1),
		par(n + 1,vector<int>(17)){} // 2 ^ 17 >= N (100,000)
	
	void AddEdge(int a,int b,int c){
		adj[a].push_back({c, b});
		adj[b].push_back({c, a});
	}
	
	void DFS(int cur,int cost, int d){
		if(vist[cur]) return;
		vist[cur] = 1;
		depth[cur] = d;
		dist[cur] = cost;
		for(auto _xt : adj[cur]){
			auto nxt = _xt.second,ncost = _xt.first;
			if(!vist[nxt]){
				par[nxt][0] = cur;
				DFS(nxt, ncost + cost, d + 1);
			}
		}
	}
	
	void MakeTable(){
		for(int j = 1; j < 17; j++){
			for(int i = 1; i <= n; i++){
				par[i][j] = par[par[i][j - 1]][j - 1];
			}
		}
	}
	
	int GetLCA(int a,int b){
		if(depth[a] < depth[b]) swap(a, b);
		int diff = depth[a] - depth[b];
		for(int i = 0; diff; i++){
			if(diff & 1) a = par[a][i];
			diff >>= 1;
		}
		if(a == b) return a;
		for(int i = 16; i >= 0; i--){
			if(par[a][i] != par[b][i]) a = par[a][i],b = par[b][i];
		}
		return par[b][0];
	}
};

void Main(){
    int n,q; cin >> n >> q;
    LCA G(n);
    for(int i = 1; i < n; i++){
        int a,b,c; cin >> a >> b >> c;
        G.AddEdge(a, b, c);
    }
    G.DFS(1, 0, 0);
    G.MakeTable();
    while(q--){
        int a,b; cin >> a >> b;
        int lca = G.GetLCA(a, b);
        cout << G.dist[a] + G.dist[b] - (G.dist[lca] << 1) << "\n";
    }
}

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed); cout.precision(PRECISION);
    Main();
    return 0;
}
