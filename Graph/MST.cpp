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

#define X first
#define Y second
#define int int_fast64_t
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define Compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())
#define OOB(x, y) ((x) < 0 || (x) >= n || (y) < 0 || (y) >= m)
#define IDX(v, x) (lower_bound(all(v), x) - (v).begin())
#define debug(x) cout << (#x) << ": " << (x) << '\n'
#define sf1(a) cin >> a
#define sf2(a, b) cin >> a >> b
#define sf3(a, b, c) cin >> a >> b >> c
#define sf4(a, b, c, d) cin >> a >> b >> c >> d
#define sf5(a, b, c, d, e) cin >> a >> b >> c >> d >> e
#define sf6(a, b, c, d, e, f) cin >> a >> b >> c >> d >> e >> f
#define pf1(a) cout << (a) << ' '
#define pf2(a, b) cout << (a) << ' ' << (b) << ' '
#define pf3(a, b, c) cout << (a) << ' ' << (b) << ' ' << (c) << ' '
#define pf4(a, b, c, d) cout << (a) << ' ' << (b) << ' ' << (c) << ' ' << (d) << ' '
#define pf5(a, b, c, d, e) cout << (a) << ' ' << (b) << ' ' << (c) << ' ' << (d) << ' ' << (e) << ' '
#define pf6(a, b, c, d, e, f) cout << (a) << ' ' << (b) << ' ' << (c) << ' ' << (d) << ' ' << (e) << ' ' << (f) << ' '
#define pf0l() cout << '\n';
#define pf1l(a) cout << (a) << '\n'
#define pf2l(a, b) cout << (a) << ' ' << (b) << '\n'
#define pf3l(a, b, c) cout << (a) << ' ' << (b) << ' ' << (c) << '\n'
#define pf4l(a, b, c, d) cout << (a) << ' ' << (b) << ' ' << (c) << ' ' << (d) << '\n'
#define pf5l(a, b, c, d, e) cout << (a) << ' ' << (b) << ' ' << (c) << ' ' << (d) << ' ' << (e) << '\n'
#define pf6l(a, b, c, d, e, f) cout << (a) << ' ' << (b) << ' ' << (c) << ' ' << (d) << ' ' << (e) << ' ' << (f) << '\n'
#define pfvec(V)            \
	for (auto const &t : V) \
	pf1(t)
#define pfvecl(V)           \
	for (auto const &t : V) \
		pf1(t);             \
	pf0l()
#define pfvecll(V)           \
	for (auto const &t : V) \
		pf1l(t);             \
	pf0l()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define EACH(x, a) for (auto& x: a)

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
template <typename T>
using wector = vector<vector<T>>;
template <typename T>
using max_heap = priority_queue<T>;
template <typename T>
using min_heap = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T> T max(vector<T> v) { return *max_element(all(v)); }
template<typename T> T min(vector<T> v) { return *min_element(all(v)); }
template<typename T> T sz(vector<T> v) { return (int)v.size(); }

template<typename T>
void read(vector<T>& v){
	EACH(i,v) sf1(i);
}

template<typename T>
void print(T arg) {
	cout << arg << '\n';
}

template<typename T, typename... Types>
void print(T arg, Types... args) {
	cout << arg << " ";
	print(args...);
}

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, 1, -1};
const int ddx[8] = {0, 0, 1, 1, 1, -1, -1, -1}, ddy[8] = {1, -1, 1, 0, -1, 1, 0, -1};
const int MOD = 1e9 + 7;
const long double EPS = 1e-12;
const int INF = 1e9 + 7;
const double PI = acos(-1);

/*
BOJ 1774번 : 우주신과 교감 AC Code
https://www.acmicpc.net/problem/1774
*/

struct UnionFind { // union-by-rank ver.
	vector<int> par, rank, cnt;
	UnionFind(int n) : par(n), rank(n, 1), cnt(n, 1) {
		iota(par.begin(), par.end(), 0);
	}
	int Find(int x) {
		return x == par[x] ? x : par[x] = Find(par[x]);
	}
	bool Union(int a, int b) {
		a = Find(a), b = Find(b);
		if (a == b) return 0;
		if (rank[a] < rank[b]) swap(a, b);
		par[b] = a;
		rank[a] += rank[a] == rank[b];
		cnt[a] += cnt[b];
		return 1;
	}
};

int n,m;
pii cod[1111];

double GetDist(pii& a, pii& b){ return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second)); }

int32_t main(){
	fastio;
	sf2(n, m);
	for(int i = 1; i <= n; i++) sf2(cod[i].first, cod[i].second);
	UnionFind UF(n + 2);
	vector<tuple<double, int, int>> e;
	int cnt = 0;
	double cost = 0.0;
	while(m--){
		int a,b; sf2(a, b);
		if(UF.Union(a, b)) cnt++;
	}
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			auto di = GetDist(cod[i], cod[j]);
			e.push_back({di, i, j});
		}
	}
	sort(all(e));
	for(auto& i : e){
		double c = get<0>(i);
		auto a = get<1>(i),b = get<2>(i);
		if(UF.Union(a, b)){
			cost += c;
			if(++cnt == n - 1) break;
		}
	}
	cout << fixed << setprecision(2) << cost << "\n";
	return 0; 
}
