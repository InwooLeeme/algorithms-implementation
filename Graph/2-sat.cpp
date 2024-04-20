struct two_sat{
	int n,c,scc_cnt;
	vector<vector<int>> adj;
	vector<int> disc,scc;
	stack<int> S;
	two_sat(int n = 0):
		n(n),c(0),disc(n + 1 << 1, 0),scc_cnt(0),
		scc(n + 1 << 1, 0),adj(n + 1 << 1){}
	
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

	int NOT(int x){ return x << 1 | 1; }

	int cvt(int x){ return x << 1; }

	void Add_Edge(int a, bool na, int b, bool nb){
		a = a << 1 | na;
		b = b << 1 | nb;
		adj[a ^ 1].push_back(b);
		adj[b ^ 1].push_back(a);
	}
	
	bool isSatisified(){
		for(int i = 1; i < (n + 1 << 1); i++){
			if(!disc[i]) DFS(i);
		}
		for(int i = 1; i <= n; i++){
			if(scc[cvt(i)] == scc[NOT(i)]) return false;			
		}
		return true;
	}

	bool get(int i) const{
		return scc[cvt(i)] < scc[NOT(i)];
	} 
};

void Main(){
	int n,m; ri(n, m);
	two_sat sat(n);
	while(m--){
		int a,b; ri(a, b);
		sat.Add_Edge(abs(a), a < 0, abs(b), b < 0);
	}
	po(sat.isSatisified());
} 
