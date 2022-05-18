#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

/* 
오일러 회로(EularCircuit)
boj 1199

*/

// 1 - indexed base //
struct EularCircuit{
	int n,id;
	vector<vector<int>> adj;
	vector<stack<pii>> v;
	vector<int> check,eularCircuit;
	
	EularCircuit(int n):
		n(n),id(0),
		adj(n + 1,vector<int>(n + 1)),v(n + 1) {}
	
	void DFS(int cur){
		while(1){
			while(!v[cur].empty() and check[v[cur].top().second]) v[cur].pop();
			if(v[cur].empty()) break;
			
			auto [x, y] = v[cur].top(); v[cur].pop();
			check[y] = 1,DFS(x);
		}
		eularCircuit.push_back(cur);
	}
	
	void AddEdge(){
		for(int i = 1; i <= n; i++){
			for(int j = i + 1; j <= n; j++){
				while(adj[i][j]){
					adj[i][j]--,id++;
					v[i].push({j, id}),v[j].push({i, id});
				}
			}
		}
		check.resize(id + 1);
	}
	
	void Excute(int root = 1){
		DFS(root);
	}
	
	bool isExit(){
		for(int i = 1; i <= n; i++)	if(v[i].size() % 2) return 0;
		return 1;
	}
	
	void Print(){
		for(const auto& i : eularCircuit) cout << i << ' ';
	}
};

int32_t main(){
	fastio;
	int n; sf1(n);
	EularCircuit EC(n);
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) sf1(EC.adj[i][j]);
	EC.AddEdge();
	if(!EC.isExit()){
		cout << -1 << "\n";
		return 0;
	}
	else{
		EC.Excute(1);
		EC.Print();
	}
}