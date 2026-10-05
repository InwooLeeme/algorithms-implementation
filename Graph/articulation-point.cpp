/*
 * BOJ 11266
 * https://www.acmicpc.net/problem/11266
 * 단절점
 */

#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

struct ArticulationPoint {
	int n, dfs_cnt = 0;
	vector<int> dfs_order, low;
	vector<char> check;
	vector<vector<int>> adj;

	explicit ArticulationPoint(int n = 0) :
		n(n), dfs_order(n + 1), low(n + 1), check(n + 1), adj(n + 1) {}

	void AddEdge(int a, int b) {
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	void DFS(int cur, int parent) {
		dfs_order[cur] = low[cur] = ++dfs_cnt;
		int children = 0;
		for (int nxt : adj[cur]) {
			if (dfs_order[nxt]) {
				low[cur] = min(low[cur], dfs_order[nxt]);
				continue;
			}
			DFS(nxt, cur);
			low[cur] = min(low[cur], low[nxt]);
			children++;
			if (parent != 0 && low[nxt] >= dfs_order[cur]) check[cur] = 1;
		}
		if (parent == 0 && children > 1) check[cur] = 1;
	}

	void GetCheck() {
		for (int i = 1; i <= n; i++)
			if (!dfs_order[i]) DFS(i, 0);
	}
};
