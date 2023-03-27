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

#define int int_fast64_t
const int INF = 1e9 + 7;

/*
HLD Template 5916 AC Code
https://www.acmicpc.net/problem/5916
Lazy + HLD (path_Update, Query)
*/

template<size_t sz>
struct SegTree {
	vector<int> tree, lazy;
	SegTree() : tree(sz << 1), lazy(sz << 1) {}
	void Push(int node, int L, int R) {
		if (node < sz) for (const int nxt : { node << 1, node << 1 | 1}) lazy[nxt] += lazy[node];
		tree[node] += lazy[node] * (R - L + 1), lazy[node] = 0;
	}
	void Update(int l, int r, int val, int node = 1, int L = 1, int R = sz) {
		Push(node, L, R);
		if (r < L || R < l) return;
		if (l <= L && R <= r) { lazy[node] += val, Push(node, L, R); return; }
		int mid = L + R >> 1;
		Update(l, r, val, node << 1, L, mid);
		Update(l, r, val, node << 1 | 1, mid + 1, R);
		tree[node] = tree[node << 1] + tree[node << 1 | 1];
	}
	int Query(int l, int r, int node = 1, int L = 1, int R = sz) {
		Push(node, L, R);
		if (r < L || R < l) return 0;
		if (l <= L && R <= r) return tree[node];
		int mid = L + R >> 1;
		return Query(l, r, node << 1, L, mid) + Query(l, r, node << 1 | 1, mid + 1, R);
	}
};

template<size_t _sz>
struct HLD {
	SegTree<1 << 17> ST;
	vector<int> cost, sz, dep, par, top, in, out;
	vector<vector<pair<int, int>>> inp;
	vector<vector<int>> adj;
	HLD() : cost(_sz), sz(_sz), dep(_sz), par(_sz), top(_sz), in(_sz), out(_sz), inp(_sz), adj(_sz) {}
	void add_edge(int a, int b, int c) { inp[a].push_back({ b, c }), inp[b].push_back({ a, c }); }
	void dfs(int cur = 1, int prev = -1) {
		for (auto [nxt, ncost] : inp[cur]) {
			if (nxt == prev) continue;
			adj[cur].push_back(nxt);
			cost[nxt] = ncost;
			dfs(nxt, cur);
		}
	}
	void dfs1(int cur = 1) {
		sz[cur] = 1;
		for (auto& nxt : adj[cur]) {
			dep[nxt] = dep[cur] + 1; par[nxt] = cur;
			dfs1(nxt); sz[cur] += sz[nxt];
			if (sz[nxt] > sz[adj[cur][0]]) swap(nxt, adj[cur][0]);
		}
	}
	int temp = 0;
	void dfs2(int cur = 1) {
		in[cur] = ++temp;
		for (auto nxt : adj[cur]) {
			top[nxt] = (nxt == adj[cur][0] ? top[cur] : nxt);
			dfs2(nxt);
		}
		out[cur] = temp;
	}
	void construct() {
		dfs(), dfs1(), dfs2(top[1] = 1);
		//for (int i = 1; in[i]; i++) ST.Update(in[i], cost[i]);
	}
	int path_query(int a, int b) {
		int ret = -INF;
		for (; top[a] ^ top[b]; a = par[top[a]]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			ret = max(ret, ST.Query(in[top[a]], in[a]));
		}
		if (dep[a] > dep[b]) swap(a, b);
		ret = max(ret, ST.Query(in[a] + 1, in[b]));
		return ret;
	}
	/* void node_update(int x, int val) {
		ST.Update(in[x], val);
	} */

    void path_query(int a, int b, int c = 1){
        while(top[a] != top[b]){
            if(dep[top[a]] < dep[top[b]]) swap(a, b);
            int st = top[a];
            ST.Update(in[st], in[a], c);
            a = par[st];
        }
        if(in[a] > in[b]) swap(a, b);
        ST.Update(in[a] + 1, in[b], c);
    }

    int Query(int a, int b){
        int ret = 0;
        while(top[a] != top[b]){
            if(dep[top[a]] < dep[top[b]]) swap(a, b);
            int st = top[a];
            ret += ST.Query(in[st], in[a]);
            a = par[st];
        }
        if(in[a] > in[b]) swap(a, b);
        ret += ST.Query(in[a] + 1, in[b]);
        return ret;
    }
};

HLD<1 << 17> hld;

int32_t main(){
    fastio;
    int n,q; cin >> n >> q;
    for(int i = 1; i < n; i++){
        int a,b; cin >> a >> b;
        hld.add_edge(a, b, 1);
    }
    hld.construct();
    while(q--){
        char c; int u,v; cin >> c >> u >> v;
        if(c == 'P') hld.path_query(u, v, 1);
        else cout << hld.Query(u, v) << "\n";
    }
    return 0;
}
