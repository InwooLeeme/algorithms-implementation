#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using namespace __gnu_cxx;

#define X first
#define Y second
#define int int64_t
#define sz(v) (int)(v).size()
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define Compress(v) sort(all(v)), (v).erase(unique(all(v)), (v).end())
#define OOB(x, y) ((x) < 0 || (x) >= n || (y) < 0 || (y) >= m)
#define IDX(v, x) (lower_bound(all(v), x) - (v).begin())
#define debug(x) cout << (#x) << ": " << (x) << '\n'

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using tii = tuple<int, int, int>;
template <typename T>
using wector = vector<vector<T>>;

/*
Binomial Coefficients AC Code
ref : https://cp-algorithms.com/combinatorics/binomial-coefficients.html
Time Complexity : O(MlogN)
Catch Time : O(1)
Problem : https://www.acmicpc.net/problem/11401
*/

const int MOD = 1e9 + 7;
int f[4000001];

// mod inverse
int minv(int x,int y){
	int p = MOD - 2;
	for(; p; p >>= 1){
		if(p & 1) x = x * y % MOD;
		y = y * y % MOD;
	}
	return x;
}

int32_t main(){
	fastio;
	int n,k; cin >> n >> k;
	f[0] = 1;
	for(int i = 1; i <= n; i++) f[i] = i * f[i - 1] % MOD;
	cout << minv(f[n], f[k] * f[n - k] % MOD) << "\n";
}
