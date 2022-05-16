/*
 * BOJ 11266
 * https://www.acmicpc.net/problem/11266
 * 단절점
 */

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct ArticulationPoint {
	int n, dfs_cnt;
	vector<int> dfs_order, check;
	vector<vector<int>> adj;

	ArticulationPoint(int n = 0) :
		n(n), adj(n + 1),
		dfs_order(n + 1), check(n + 1),
		dfs_cnt(0) {}

	void AddEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int DFS(int cur, bool IsRoot = 0) {
		int ret = dfs_order[cur] = ++dfs_cnt, cnt = 0;
		for (const auto& nxt : adj[cur]) {
			if (!dfs_order[nxt]) {
				const int t = DFS(nxt);
				if (t >= dfs_order[cur]) check[cur] = 1;
				ret = min(ret, t), cnt++;
			}
			else ret = min(ret, dfs_order[nxt]);
		}
		if (IsRoot) check[cur] = cnt > 1;
		return ret;
	}

	void GetCheck() {
		for (int i = 1; i <= n; i++)
			if (!dfs_order[i]) DFS(i, 1);
	}
};