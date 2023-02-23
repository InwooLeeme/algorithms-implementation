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
#define SZ(v) (int)(v).size()
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
#define rep1(i,n) for(int i=1;i<=(n);i++)
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
const int INF = 0x3f3f3f3f;
const double PI = acos(-1);

/*
https://www.acmicpc.net/problem/15483 : 최소 편집
15483 AC Code
ref : https://nicotina04.tistory.com/196
*/

int d[1111][1111]; // d[i][j] : 문자열 a에서 길이 i만큼의 prefix와 문자열 b에서 길이 j만큼의 prefix를 같게 만드는 최소 편집 거리
// d[i][j] = d[i][j] = d[i - 1][j - 1] if : a[i - 1] == b[j - 1] else : min(d[i - 1][j - 1], d[i - 1][j], d[i][j - 1]) + 1

int32_t main(){
	fastio;
	string a,b; sf2(a, b);
	for(int i = 0; i < SZ(a); i++) d[i + 1][0] = i + 1;
	for(int i = 0; i < SZ(b); i++) d[0][i + 1] = i + 1;
	for(int i = 1; i <= SZ(a); i++){
		for(int j = 1; j <= SZ(b); j++){
			if(a[i - 1] == b[j - 1]) d[i][j] = d[i - 1][j - 1];
			else d[i][j] = min<int>({d[i - 1][j], d[i - 1][j - 1], d[i][j - 1]}) + 1;
		}
	}
	pf1l(d[SZ(a)][SZ(b)]);
	return 0; 
}
