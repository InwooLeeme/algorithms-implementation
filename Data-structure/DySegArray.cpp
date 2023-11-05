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

template<typename T>
void printv(vector<T> v) {
	for (auto e : v) {
		cout << e << " ";
	}   cout << "\n";
}
 
template<typename T>
void printvv(vector<T> vv) {
	for (int i=0; i<vv.size(); i++) {
		cout << i << ": ";
		for (auto e : vv[i]) {
			cout << e << " ";
		}   cout << "\n";
	}
}

template<typename T>
void ri(T &x) {
	cin >> x;
}
template<typename T, typename... Args>
void ri(T &x, Args&... args) {
	ri(x);
	ri(args...) ;
}
template<typename T>
void ri(vector<T> &v) {
	for (auto &x : v) {
		cin >> x;
	}
}
template<typename T, typename... Args>
void ri(vector<T> &v, Args&... args) {
	ri(v);
	ri(args...);
}

template<typename T>
void po(T x) {
	cout << x << "\n";
}
template<typename T, typename... Args>
void po(T x, Args... args) {
	cout << x << " ";
	po(args...) ;
}
template<typename T>
void po(vector<T> &a) {
	for (int i=0; i<(int)a.size(); i++) {
		if (i <(int)a.size()-1) {
			cout << a[i] << " ";
		}
		else cout << a[i] << "\n";
	}
}

void __print(int x) {cerr << x;}
void __print(signed x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T1, typename T2, typename T3>
void __print(const tuple<T1, T2, T3> &x) {cerr << '{'; __print(get<0>(x)); cerr << ','; __print(get<1>(x)); cerr << ','; __print(get<2>(x)); cerr << '}';}
template<typename T1, typename T2, typename T3, typename T4>
void __print(const tuple<T1, T2, T3, T4> &x) {cerr << '{'; __print(get<0>(x)); cerr << ','; __print(get<1>(x)); cerr << ','; __print(get<2>(x)); cerr << ','; __print(get<3>(x)); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
template<typename T1, typename T2>
void __print(map<T1,T2> &mp) {for (auto [k,v] : mp) {cerr << '{'; __print(k); cerr << ':'; __print(v); cerr << '}';}}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

int cnt_leq_x(vi &a, int x) {
	return upper_bound(a.begin(), a.end(), x) - a.begin();
}

int cnt_leq_x(vi &a, int x, int lo, int hi) {
	return upper_bound(a.begin()+lo, a.begin()+hi, x) - a.begin()+lo;
}

int cnt_lt_x(vi &a, int x) {
	return lower_bound(a.begin(), a.end(), x) - a.begin();
}

int cnt_lt_x(vi &a, int x, int lo, int hi) {
	return lower_bound(a.begin()+lo, a.begin()+hi, x) - a.begin()+lo;
}

int cnt_geq_x(vi &a, int x) {
	return a.end() - lower_bound(a.begin(), a.end(), x);
}

int cnt_geq_x(vi &a, int x, int lo, int hi) {
	return a.begin()+hi - lower_bound(a.begin()+lo, a.begin()+hi, x);
}

int cnt_gt_x(vi &a, int x) {
	return a.end() - upper_bound(a.begin(), a.end(), x);
}

int cnt_gt_x(vi &a, int x, int lo, int hi) {
	return a.begin()+hi - upper_bound(a.begin()+lo, a.begin()+hi, x);
}

bool mul_overflow(int a, int b) {
	int c;
	return __builtin_mul_overflow(a, b, &c);
}

template<typename T>
int popcount(T x) {return __builtin_popcount(x);}

template<typename T>
T sum(vector<T> &a) {
	T ret = 0;
	for (auto v : a) ret += v;
	return ret;
}

template<typename T>
T max(vector<T> &a) {
	return *max_element(a.begin(), a.end());
}

template<typename T>
T min(vector<T> &a) {
	return *min_element(a.begin(), a.end());
}

int ceil_div(int a, int b) {
	return (a + b - 1) / b;
}

int int_pow(int base, int exp) {
	int res = 1;
	while (exp) {
		if (exp & 1) res *= base;
		exp >>= 1;
		base *= base;
	}
	return res;
}

int highest_power_of_2(int n) {
	while((n & (n-1)) != 0){
		n = n & (n-1);
	}
	return n;
}

int msb_pos(int x) {
	if (x==0) return -1;
	int y = __builtin_clzll(x);
	int ret = 63 - y;
	return ret;
}

template<typename T>
void chmax(T &x, T y) {x = max(x,y);}

template<typename T>
void chmin(T &x, T y) {x = min(x,y);}

template<typename T>
void asort(vector<T> &a) {sort(a.begin(), a.end());}

template<typename T>
void dsort(vector<T> &a) {sort(a.rbegin(), a.rend());}

template<typename T>
void reverse(vector<T> &a) {reverse(a.begin(), a.end());}

template<typename T>
set<T> get_set(vector<T> &a) {
	set<T> ret(a.begin(), a.end());
	return ret;
}

template<typename T>
vector<T> get_unique(vector<T> a) {
	asort(a);
	a.erase(unique(a.begin(), a.end()), a.end());
	return a;
}

vs Split(string& s){
	string temp; 
	vs ret;
	stringstream in(s);
	while(in >> temp) ret.push_back(temp);
	return ret;
}

int LIS(vi& v){
	vi LIS;
	for(auto& i : v){
		if(LIS.empty() or LIS.back() < i) LIS.push_back(i);
		else *lower_bound(LIS.begin(), LIS.end(), i) = i;
	}
	return LIS.size();
}

int LDS(vi& v){
	vi LDS;
	for(auto& i : v){
		auto t = -i;
		if(LDS.empty() or LDS.back() < t) LDS.push_back(t);
		else *lower_bound(LDS.begin(), LDS.end(), t) = t;
	}
	return LDS.size();
}

int _pow(int x, int n){
    int ret = 1;
    while(n){
        if(n & 1) ret = ret * x;
        x = x * x;
        n >>= 1;
    }
    return ret;
}

int _pow(int x, int n, int MOD) {
    int ret = 1;
	while(n){
		if(n & 1) ret = ret * x % MOD;
		x = x * x % MOD;
		n >>= 1;
	}
	return ret % MOD;
}

constexpr int INF = int(2e18);

const int PRECISION = 0;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const int ddx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
const int ddy[8] = {0, 1, 0, -1, 1, -1, -1, 1};

// Dynamic Segment Tree array ver.
// Problem : https://www.acmicpc.net/problem/14577
// ref : https://justicehui.github.io/medium-algorithm/2020/02/28/DynamicSeg/

struct Node{
	int l,r,v;
	Node(){ l = r = -1; v = 0;}	
};

Node T[4040404];
int sz = 1;

void Update(int node, int x, int v, int s = 0, int e = int(1e18 + 5)){
	if(s == e){ T[node].v = v; return; }
	int m = s + e >> 1;
	if(x <= m){
		if(T[node].l == -1) T[node].l = sz++;
		Update(T[node].l, x, v, s, m);
	}
	else{
		if(T[node].r == -1) T[node].r = sz++;
		Update(T[node].r, x, v, m + 1, e);
	}
	int t1 = T[node].l != -1 ? T[T[node].l].v : 0;
	int t2 = T[node].r != -1 ? T[T[node].r].v : 0;
	T[node].v = t1 + t2;
}

int Query(int node, int l, int r, int s = 0, int e = int(1e18 + 5)){
	if(node == -1) return 0;
	if(r < s or e < l) return 0;
	if(l <= s and e <= r) return T[node].v;
	int m = s + e >> 1;
	return Query(T[node].l, l, r, s, m) + Query(T[node].r, l, r, m + 1, e);
}

int Kth(int node, int k, int s = 0, int e = int(1e18 + 5)){
	if(s == e) return e;
	int m = s + e >> 1;
	int lval = T[T[node].l].v;
	if(lval >= k) return Kth(T[node].l, k, s, m);
	return Kth(T[node].r, k - lval, m + 1, e);
}

void Main(){
	int n,q; ri(n, q);
	vi v(n + 1);
	for(int i = 1; i <= n; i++){
		ri(v[i]);
		int cur = Query(0, v[i], v[i]);
		Update(0, v[i], cur + 1);
	}
	while(q--){
		int t,a,b; ri(t);
		if(t == 1){
			ri(a, b);
			int prv = Query(0, v[a], v[a]);
			Update(0, v[a], prv - 1);
			v[a] += b;
			int cur = Query(0, v[a], v[a]);
			Update(0, v[a], cur + 1);
		}
		else if(t == 2){
			ri(a, b);
			int prv = Query(0, v[a], v[a]);
			Update(0, v[a], prv - 1);
			v[a] -= b;
			int cur = Query(0, v[a], v[a]);
			Update(0, v[a], cur + 1);
		}
		else if(t == 3){
			ri(a, b);
			po(Query(0, a, b));
		}
		else if(t == 4){
			ri(a);
			po(Kth(0, n - a + 1));
		}
	}
}	

int32_t main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed); cout.precision(PRECISION);
	Main();
	return 0;
}
