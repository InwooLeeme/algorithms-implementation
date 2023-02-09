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
#define X first
#define Y second

using pii = pair<int, int>;

/*
 https://www.acmicpc.net/problem/11012
11012 AC Code
PST Implement Code
*/

struct PST {
	struct Node {
		int l, r, sum;
		Node() : l(-1), r(-1), sum(0) {}
		Node(int sum) : l(-1), r(-1), sum(sum) {}
		Node(int l, int r, int sum) : l(l), r(r), sum(sum) {}
	};
	vector<Node> nodes;
	vector<int> roots;
	int sz;
	PST(int sz) : sz(sz) {
		roots.push_back(init(0, sz));
	}
	int init(int L, int R) {
		if (L == R) nodes.push_back(0);
		else {
			int mid = L + R >> 1;
			nodes.push_back({ init(L, mid), init(mid + 1, R), 0 });
		}
		return nodes.size() - 1;
	}
	int update(int i, int val, int L, int R, int nodeNum) {
		Node cur = nodes[nodeNum];
		if (L == R) nodes.push_back(cur.sum + val);
		else {
			int mid = L + R >> 1;
			if (i <= mid) {
				int l = update(i, val, L, mid, cur.l);
				nodes.push_back({ l, cur.r, cur.sum + val });
			}
			else {
				int r = update(i, val, mid + 1, R, cur.r);
				nodes.push_back({ cur.l, r, cur.sum + val });
			}
		}
		return nodes.size() - 1;
	}
	void update_x(int i, int val) {
		roots.back() = update(i, val, 0, sz, roots.back());
	}
	void update_y() {
		roots.push_back(roots.back());
	}
	int sum(int L, int R, int nodeNum, int nodeL, int nodeR) {
		Node cur = nodes[nodeNum];
		if (L > R) return 0;
		if (R < nodeL || nodeR < L) return 0;
		if (L <= nodeL && nodeR <= R) return cur.sum;
		int mid = nodeL + nodeR >> 1;
		return sum(L, R, cur.l, nodeL, mid) + sum(L, R, cur.r, mid + 1, nodeR);
	}
	int sum(int xl, int xr, int y) {
		return sum(xl, xr, roots[y], 0, sz);
	}
	int sum(int xl, int xr, int yl, int yr) {
		if (yl <= 0) return sum(xl, xr, yr);
		return sum(xl, xr, yr) - sum(xl, xr, yl - 1);
	}
};

int32_t main(){
    fastio;
    int t; cin >> t;
    while(t--){
        int n,q; cin >> n >> q;
        vector<pii> v(n);
        for(auto& [a, b] : v) cin >> a >> b;
        sort(v.begin(), v.end(), [&](pii&a ,pii& b){
            return a.Y < b.Y || a.Y == b.Y && a.X < b.X;
        }); 
        PST PST(100000);
        for(int i = 0,idx = 0; i <= 100000; i++){
            while(idx < n and v[idx].Y == i){
                PST.update_x(v[idx].X, 1);
                idx++;
            }
            PST.update_y();
        }
        int ret = 0;
        while(q--){
            int r1,c1,r2,c2; cin >> r1 >> r2 >> c1 >> c2;
            ret += PST.sum(r1, r2, c1, c2);
        }
        cout << ret << '\n';
    }
    return 0;
}
