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

#define int int64_t

// 1 - indexed base // 
struct BM{
	int n;
	vector<vector<int>> adj;
	vector<int> par;
	vector<bool> match;
	
	BM(int n = 0): n(n),adj(n + 1),par(n + 1, -1),match(n + 1, 0){}
	void AddEdge(int a,int b){ adj[a].push_back(b);}
	
	int DFS(int cur){
		for(auto nxt : adj[cur]){
			if(match[nxt]) continue;
			match[nxt] = 1;
			if(par[nxt] == -1 or DFS(par[nxt])){
				par[nxt] = cur;
				return 1;
			}
		}
		return 0;
	}
	
	int Matching(){
		int ret = 0;
		for(int i = 1; i <= n; i++){
			fill(match.begin(), match.end(), 0);
			ret += DFS(i);
		}
		return ret;
	}
};

int32_t main(){
  fastio;
  int n; cin >> n;
  BM G(n);
  
  return 0;
}
