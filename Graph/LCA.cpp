#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

/* 1 - indexed base */
struct LCA{
	int n;
	vector<vector<int>> adj,par;
	vector<int> depth,vist;
	
	LCA(int n = 0):
		n(n),adj(n + 1),depth(n + 1),vist(n + 1),
		par(n + 1,vector<int>(30)){}
	
	void AddEdge(int a,int b){
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	void DFS(int cur,int d){
		if(vist[cur]) return;
		vist[cur] = 1;
		depth[cur] = d;
		for(auto nxt : adj[cur]){
			if(!vist[nxt]){
				par[nxt][0] = cur;
				DFS(nxt, d + 1);
			}
		}
	}
	
	void MakeTable(){
		for(int j = 1; j < 30; j++){
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
		for(int i = 29; i >= 0; i--){
			if(par[a][i] != par[b][i]) a = par[a][i],b = par[b][i];
		}
		return par[b][0];
	}
};

int main(){
	fastio;
	int n; sf1(n);
	LCA L(n);
	for(int i = 1; i < n; i++){
		int a,b; sf2(a, b);
		L.AddEdge(a, b);
	}
	L.DFS(1, 0);
	L.MakeTable();
	int q; sf1(q);
	while(q--){
		int u,v; sf2(u, v);
		pf1l(L.GetLCA(u, v));
	}
}