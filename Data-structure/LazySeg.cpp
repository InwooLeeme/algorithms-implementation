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


struct SegTree {
	ll tree[1 << 21], lazy[1 << 21]; //arr[0, n-1] -> tree[sz, sz + n - 1]
	int sz = 1 << 20;

	void construct() {
		for (int i = sz - 1; i > 0; i--) {
			tree[i] = tree[i << 1] + tree[i << 1 | 1];
		}
	}
	void propagate(int node, int nodeL, int nodeR) {
		if (lazy[node]) {
			if (node < sz) {
				lazy[node << 1] += lazy[node];
				lazy[node << 1 | 1] += lazy[node];
			}
			tree[node] += lazy[node] * (nodeR - nodeL + 1);
			lazy[node] = 0;
		}
	}
	//[l, r] += k
	void update(int L, int R, int k, int nodeNum, int nodeL, int nodeR) {
		propagate(nodeNum, nodeL, nodeR);
		if (R < nodeL || nodeR < L) return;
		if (L <= nodeL && nodeR <= R) {
			lazy[nodeNum] += k;
			propagate(nodeNum, nodeL, nodeR);
			return;
		}
		int mid = nodeL + nodeR >> 1;
		update(L, R, k, nodeNum << 1, nodeL, mid);
		update(L, R, k, nodeNum << 1 | 1, mid + 1, nodeR);
		tree[nodeNum] = tree[nodeNum << 1] + tree[nodeNum << 1 | 1];
	}
	void update(int l, int r, int k) {
		update(l, r, k, 1, 1, sz);
	}
	//[l, r] : 1-indexed
	ll query(int L, int R, int nodeNum, int nodeL, int nodeR) {
		propagate(nodeNum, nodeL, nodeR);
		if (R < nodeL || nodeR < L) return 0;
		if (L <= nodeL && nodeR <= R) return tree[nodeNum];
		int mid = nodeL + nodeR >> 1;
		return query(L, R, nodeNum << 1, nodeL, mid) + query(L, R, nodeNum << 1 | 1, mid + 1, nodeR);
	}
	ll query(int l, int r) {
		return query(l, r, 1, 1, sz);
	}
} ST;

int32_t main(){
  fastio;
  return 0;
}
