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

/*
최소 외접원 AC Code 
problem : https://www.acmicpc.net/problem/2626
ref)
https://justicehui.github.io/hard-algorithm/2020/03/23/random/
*/

namespace SmallestEnclosingCircle{
    struct pt{
        long double x,y;
        pt operator + (pt const& a){ return {x + a.x, y + a.y}; }
        pt operator - (pt const& a){ return {x - a.x, y - a.y}; }
        pt operator - (){ return {-x, -y}; }
        pt operator * (long double a) { return {x * a, y * a}; }
        pt operator / (long double a) { return {x / a, y / a}; }
    };
    long double inner_product(pt a, pt b){ return a.x * b.x + a.y * b.y; }
    long double outer_product(pt a, pt b){ return a.x * b.y - a.y * b.x; }
    long double dist(pt a,pt b) { return hypot<long double>(a.x - b.x, a.y - b.y); }
    
    // 외심
    pt CenterMeter(pt a, pt b, pt c){
        pt ab = b - a, ac = c - a;
        auto c1 = inner_product(ab, ab) / 2, c2 = inner_product(ac, ac) / 2;
        auto d = outer_product(ab, ac);
        auto x = a.x + (c1 * ac.y - c2 * ab.y) / d;
        auto y = a.y + (c2 * ab.x - c1 * ac.x) / d;
        return {x, y};
    }

    struct circle{
        pt p; double r;
    };

    circle Sol(vector<pt> v){
        pt p = { 0, 0 }; double r = 0;
		int n = v.size();
		for (int i = 0; i < n; i++) if (dist(p, v[i]) > r) {
			p = v[i], r = 0;
			for (int j = 0; j < i; j++) if (dist(p, v[j]) > r) {
				p = (v[i] + v[j]) / 2, r = dist(p, v[i]);
				for (int k = 0; k < j; k++) if (dist(p, v[k]) > r) {
					p = CenterMeter(v[i], v[j], v[k]), r = dist(p, v[k]);
				}
			}
		}
		return { p, r };
    }
};

int32_t main(){
    fastio;
    int n; cin >> n;
    vector<SmallestEnclosingCircle::pt> v(n);
    for(auto& [a, b] : v) cin >> a >> b;
    auto ret = SmallestEnclosingCircle::Sol(v);
    cout << fixed << setprecision(3) << ret.p.x << " " << ret.p.y << "\n" << ret.r << "\n";
    return 0;
}
