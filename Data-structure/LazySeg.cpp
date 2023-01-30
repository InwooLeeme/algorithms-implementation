#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int int_fast64_t
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

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

int32_t main(){
  fastio;
  return 0;
}
