#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t

const int PRECISION = 0;

/*
Find Kth Element using Segment Tree with Parametric Search
Problem : BOJ군인 https://www.acmicpc.net/problem/1321
AC Code
*/

template<typename T = int64_t, size_t sz = 17, typename F = plus<T>>
struct SegTree {
	vector<T> tree; T t; F f{};
	SegTree(T t = T()) : tree(1 << sz + 1, t), t(t) {}
	explicit SegTree(T t, const F& f) : tree(1 << sz + 1, t), t(t), f(f) {}
	
	void Init() {
    for (int i = (1 << sz) - 1; i; i--) {
      tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
    }
  }

	void Update(int i, T val) {
		--i |= 1 << sz; tree[i] += val;
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
  T sol(int k){
    int lo = 0,hi = 1000000;
    while(lo + 1 < hi){
      int mid = (lo + hi) >> 1;
      if(Query(1, mid) < k) lo = mid;
      else hi = mid;
    }
    return hi;
  }
};

void Sol(){
    int n, q; cin >> n; 
    SegTree<int, 20> ST;
    for(int i = 1, t; i <= n; i++) cin >> t,ST.Update(i, t);
    cin >> q; while(q--){
        int t,a,b; cin >> t >> a;
        if(t == 1) cin >> b, ST.Update(a, b);
        else cout << ST.sol(a) << "\n";
    }
}

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed); cout.precision(PRECISION);
    Sol();
    return 0;
}
