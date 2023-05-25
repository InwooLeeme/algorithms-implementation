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

using td3 = tuple<double, double, double>;

/* 
return raius Encolsing_Sphere using 경사 하강법
*/

namespace Cover3D{
	using td3 = tuple<double, double, double>;
	double EnclosingSphere(vector<td3>& v){
		const int n = v.size();
		double x = 0, y = 0, z = 0;
		// Input
		for (int i = 0; i < n; i++) {
			double a, b, c; cin >> a >> b >> c;
			x += a, y += b, z += c;
			v[i] = { a, b, c };
		}
		x /= n, y /= n, z /= n;
		double ratio = 0.1, ret = 0;
		for (int _ = 0; _ < 20000; _++) { // 20000
			int idx = -1;
			ret = 0;
			for (int i = 0; i < n; i++) {
				auto& [a, b, c] = v[i];
				double dist = (x - a) * (x - a) + (y - b) * (y - b) + (z - c) * (z - c);
				if (ret < dist) {
					idx = i;
					ret = dist;
				}
			}
			auto& [a, b, c] = v[idx];
			x += (a - x) * ratio;
			y += (b - y) * ratio;
			z += (c - z) * ratio;
			ratio *= 0.999;
		}
		return sqrt(ret);
	}
};

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n;
	while(cin >> n and n){
		vector<td3> v(n);
		auto ret = Cover3D::EnclosingSphere(v);
		cout << fixed << setprecision(5) << ret << "\n";
	}
    return 0;
}
