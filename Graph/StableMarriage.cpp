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

// problem url : https://www.acmicpc.net/problem/12022
// ref : https://github.com/justiceHui/icpc-teamnote/blob/master/code/Graph/StableMarriage.cpp
// man : 1 ~ n, woman : n + 1 ~ 2*n
struct StableMatching{
	int n; 
	vector<vector<int>> G;
	StableMatching(int sz):n(sz),G(2*sz + 1){
		for(int i = 1; i <= n + n; i++) G[i].reserve(n);
	}
	void AddEdge(int a, int b){ G[a].push_back(b); } //insert in decreasing order of preference.
	vector<int> Matching(){
		vector<int> match(2*n + 1), p(2*n + 1);
		queue<int> Q;
		for(int i = 1; i <= n; i++) Q.push(i);
		while(Q.size()){
			auto cur = Q.front(); Q.pop();
			for(auto& nxt : G[cur]){
				if(!match[nxt]){ match[cur] = nxt; match[nxt] = cur; break; }
				auto m = match[nxt];
				int a = -1, b = -1;
				for(int k = 0; k < G[nxt].size(); k++){
					if(G[nxt][k] == cur) a = k;
					if(G[nxt][k] == m) b = k;
				}
				if(a < b){
					match[m] = 0; Q.push(m); match[cur] = nxt; match[nxt] = cur; break;
				}
			}
		}
		return match;
	}
};

void Main(){
	int n; ri(n);
	StableMatching G(n);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			int t; ri(t);
			G.AddEdge(i, t + n);
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			int t; ri(t);
			G.AddEdge(i + n, t);
		}
	}
	auto ret = G.Matching();
	for(int i = 1; i <= n; i++) po(ret[i] - n);
} 

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed); cout.precision(PRECISION);
    Main();
    return 0;
}
