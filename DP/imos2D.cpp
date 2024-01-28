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
#define fup(i,a,b,c) for(int (i)=(a);(i)<=(b);(i)+=(c))
#define fdn(i,a,b,c) for(int (i)=(a);(i)>=(b);(i)-=(c))
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

using ld = long double;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int,int>;
using vp = vector<pii>;
using vvp = vector<vp>;
using vs = vector<string>;
using vvs = vector<vs>;
using ti3 = tuple<int,int,int>;
using vti3 = vector<ti3>;
using ll = long long;
using ull = unsigned long long;

template<typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template<typename T>
using max_pq = priority_queue<T>;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T, typename V, class cmp = less<T>>
using ordered_map = tree<T, V, cmp, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
using multi_ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

using T = array<int, 4>;

void Main(){ 
	int n,q; ri(n, q);
	vvi v(1010, vi(1010)), P(1010, vi(1010));
	for(int i = 1; i <= n; i++) for(int j = 1; j <= n; j++) ri(v[i][j]);
	vector<T> query;
	while(q--){
		int t,a,b,c,d; ri(t, a, b, c, d); ++a,++b,++c,++d;
		if(t == 1){
			int x; ri(x);
			P[a][b] += x;
			P[c + 1][b] -= x;
			P[a][d + 1] -= x;
			P[c + 1][d + 1] += x;
		}
		else query.push_back({a, b, c, d});
	}
	for(int i = 1; i < 1010; i++) for(int j = 1; j < 1010; j++){
		P[i][j] += P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1];
		v[i][j] += v[i - 1][j] + v[i][j - 1] - v[i - 1][j - 1] + P[i][j];
	}
	for(const auto& [x1, y1, x2, y2] : query){
		po(v[x2][y2] - v[x1 - 1][y2] - v[x2][y1 - 1] + v[x1 - 1][y1 - 1]);
	}
}		

int32_t main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed); cout.precision(PRECISION);
	Main();
	return 0;
} 
