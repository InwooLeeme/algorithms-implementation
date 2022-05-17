#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct SCC {
	int n, scc_cnt, dfs_cnt;
	vector<vector<int>> adj;
	vector<int> scc, dfs_order;
	stack<int> S;

	SCC(int n = 0) :
		n(n), dfs_order(n + 1),
		adj(n + 1), scc(n + 1),
		scc_cnt(0), dfs_cnt(0) {}

	void AddEdge(int a, int b) { adj[a].push_back(b); }

	int DFS(int cur) {
		int ret = dfs_order[cur] = ++dfs_cnt; S.push(cur);
		for (const auto& nxt : adj[cur]) {
			if (!dfs_order[nxt]) ret = min(ret, DFS(nxt));
			else if (!scc[nxt]) ret = min(ret, dfs_order[nxt]);
		}
		if (ret == dfs_order[cur]) {
			for (scc_cnt++; S.size();) {
				int t = S.top(); S.pop();
				scc[t] = scc_cnt;
				if (t == cur) break;
			}
		}
		return ret;
	}

	void GetSCC() {
		for (int i = 1; i <= n; i++)
			if (!dfs_order[i]) DFS(i);
	}
};

int main() {
	fastio;
}