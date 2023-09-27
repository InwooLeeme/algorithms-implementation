#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

template<typename T = int64_t, size_t sz = 20, typename F = plus<T>>
struct SegTree {
	vector<T> tree; T t; F f{};
	SegTree(T t = T()) : tree(1 << sz + 1, t), t(t) {}
	explicit SegTree(T t, const F& f) : tree(1 << sz + 1, t), t(t), f(f) {}

	void Update(int i, T val) {
		--i |= 1 << sz; tree[i] = val;
		while (i >>= 1) tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
	}
	T Query(int l, int r) {
		T L = t, R = t; --l |= 1 << sz, --r |= 1 << sz;
		while (l <= r) {
			if (l & 1) L = f(L, tree[l++]);
			if (~r & 1) R = f(tree[r--], R);
			l >>= 1, r >>= 1;
		}
		return f(L, R);
	}
};

// easy ver
struct SegTree{
	int sz = 1 << 17;
	vector<int> tree;
	
	SegTree():tree(sz << 1){}

	void Build(){
		for(int i = sz - 1; i >= 1; i--) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}
	
	void Update(int i, int val){
		i |= sz; tree[i] = val;
		while(i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}

	int Query(int l, int r){
		int ret = 0;
		l |= sz, r |= sz;
		while(l <= r){
			if(l & 1) ret += tree[l++];
			if(~r & 1) ret += tree[r--];
			l >>= 1; r >>= 1;
		}
		return ret;
	}
} ST;

SegTree ST;

int main() {
	fastio;
    // using example
	int n, m, k; cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		int64_t t; cin >> t;
		ST.Update(i, t);
	}
	for (int q = m + k; q--;) {
		int64_t t, a, b; cin >> t >> a >> b;
		if (t & 1) ST.Update(a, b);
		else cout << ST.Query(a, b) << '\n';
	}
}
