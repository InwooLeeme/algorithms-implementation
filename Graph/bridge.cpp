/*
 * 단절선
 * BOJ 11400
 * https://www.acmicpc.net/problem/11400
 */

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct Bridge { // must be no multi-edge
	int n, dfs_cnt;
	vector<int> dfs_order;
	vector<pair<int, int>> bridge;
	vector<vector<int>> adj;

	Bridge(int n = 0) :
		n(n), adj(n + 1),
		dfs_order(n + 1),
		dfs_cnt(0) {}

	void AddEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int DFS(int cur, int prv = -1) {
		int ret = dfs_order[cur] = ++dfs_cnt;
		for (const auto& nxt : adj[cur]) {
			if (nxt == prv) continue;
			if (!dfs_order[nxt]) {
				const int t = DFS(nxt, cur);
				if (t > dfs_order[cur]) bridge.push_back({ cur, nxt });
				ret = min(ret, t);
			}
			else ret = min(ret, dfs_order[nxt]);
		}
		return ret;
	}

	void GetBridge() {
		for (int i = 1; i <= n; i++)
			if (!dfs_order[i]) DFS(i);
		for (auto& [a, b] : bridge) if (a > b) swap(a, b);
		sort(bridge.begin(), bridge.end());
	}
};