struct TwoSAT{
	int n,c,scc_cnt;
	vector<vector<int>> adj;
	vector<int> disc,scc;
	stack<int> S;
	TwoSAT(int n = 0):
		n(n),c(0),disc((n << 1) + 1, 0),scc_cnt(0),
		scc((n << 1) + 1, 0),adj((n << 1) + 1){}
	
	int DFS(int cur){
		S.push(cur);
		disc[cur] = ++c;
		int ret = disc[cur];
		for(auto nxt : adj[cur]){
			if(!disc[nxt]) ret = min(ret, DFS(nxt));
			else if(!scc[nxt]) ret = min(ret, disc[nxt]);
		}
		if(ret == disc[cur]){
			scc_cnt++;
			while(S.size()){
				int h = S.top(); S.pop();
				scc[h] = scc_cnt;
				if(h == cur) break;
			}
		}
		return ret;
	}
	int cvt(int x){ return (x <= n ? x + n : x - n); }
	
	void AddEdge(int a,int b){
		adj[cvt(a)].push_back(b);
		adj[cvt(b)].push_back(a);
	}
	
	bool isSatisified(){
		for(int i = 1; i <= n << 1; i++){
			if(!disc[i]) DFS(i);
		}
		for(int i = 1; i <= n; i++){
			if(scc[i] == scc[cvt(i)]) return false;			
		}
		return true;
	}
};