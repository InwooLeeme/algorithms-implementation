#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

/* 
    Using in BOJ 2042
*/

struct SegTree {
	int tree[1 << 21]; //arr[0, n-1] -> tree[sz, sz + n - 1]
	int sz = 1 << 20;

	void construct() {
		for (int i = sz - 1; i > 0; i--) {
			tree[i] = tree[i << 1] + tree[i << 1 | 1];
		}
	}
	//i : 1-indexed
	void Update(int i, int val) {
		--i |= sz; tree[i] = val;
		while (i >>= 1) {
			tree[i] = tree[i << 1] + tree[i << 1 | 1];
		}
	}
	//[l, r] : 1-indexed
	int query(int L, int R, int nodeNum, int nodeL, int nodeR) {
		if (R < nodeL || nodeR < L) return 0;
		if (L <= nodeL && nodeR <= R) return tree[nodeNum];
		int mid = nodeL + nodeR >> 1;
		return query(L, R, nodeNum * 2, nodeL, mid) + query(L, R, nodeNum * 2 + 1, mid + 1, nodeR);
	}
	int Query(int l, int r) {
		return query(l, r, 1, 1, sz);
	}
} ST;


int32_t main(){
    int n, m, k; cin >> n >> m >> k;
	for (int i = 0; i < n; i++) cin >> ST.tree[ST.sz + i];
	ST.construct();
	for (int i = 0; i < m + k; i++) {
		int t, a, b; cin >> t >> a >> b;
		if (--t) cout << ST.Query(a, b) << '\n';
		else ST.Update(a, b);
	}
}