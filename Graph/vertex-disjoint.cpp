/*
 * reference : https://koosaga.com/76, https://github.com/koosaga/DeobureoMinkyuParty
 */

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

// 1 - indexed base // 
struct BCC { // vertex-disjoint BCC
	int n, dfs_cnt, color_cnt, art_point_cnt;
	vector<int> dfs_order, low, check;
	vector<vector<int>> adj, v, color;

	BCC(int n) :
		n(n), adj(n + 1), v(n + 1),
		dfs_order(n + 1), low(n + 1),
		check(n + 1), color(n + 1),
		dfs_cnt(0), color_cnt(0), art_point_cnt(0) {}

	void AddEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int DFS(int cur, bool IsRoot = 0) {
		int& ret = low[cur] = dfs_order[cur] = ++dfs_cnt, cnt = 0;
		for (const auto& nxt : adj[cur]) {
			if (!dfs_order[nxt]) {
				const int t = DFS(nxt);
				if (t >= dfs_order[cur] && !IsRoot && !check[cur])
					check[cur] = ++art_point_cnt;
				ret = min(ret, t), cnt++;
			}
			else ret = min(ret, dfs_order[nxt]);
		}
		if (IsRoot) check[cur] = cnt > 1 ? ++art_point_cnt : 0;
		return ret;
	}

	void Color(int cur, int p = 0) {
		if (p) { // cur != root
			color[p].push_back(cur);
			v[cur].push_back(p);
		}
		for (const auto& nxt : adj[cur]) {
			if (nxt == cur || v[nxt].size()) continue;
			if (low[nxt] >= dfs_order[cur]) {
				color[++color_cnt].push_back(cur);
				v[cur].push_back(color_cnt);
				Color(nxt, color_cnt);
			}
			else Color(nxt, p);
		}
	}

	void Init(bool flag = 0) { // suppose that graph is connected, no multi-edge, V >= 2
		DFS(1, 1); Color(1, 0);

		if (flag) {
			cout << '\n' << "articulation-point :" << '\n';
			cout << art_point_cnt << '\n';
			for (int i = 1; i <= n; i++) if (check[i]) cout << i << ' ';
			cout << "\n\n";

			cout << "color :" << '\n';
			for (int i = 1; i <= color_cnt; i++) {
				for (const auto& j : color[i]) cout << j << ' ';
				cout << '\n';
			}
		}
	}
};

int main(){
	fastio;
	int n, m; cin >> n >> m;
	BCC Graph(n);
	while (m--) {
		int a, b; cin >> a >> b;
		Graph.AddEdge(a, b);
	}
	Graph.Init(1);
}