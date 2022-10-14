#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

using ll = long long;

// CC : Coin Change 
int Sol(const vector<int>& coins, int n,int k){
	vector<int> d(10001,0);
	d[0] = 1; // 하나도 사용하지 않음.
	for(const auto& x : coins){ // 각 코인 리스트를 돌면서
		for(int i = 1; i <= k; i++){ // 모든 금액 돌면서
			if(i >= x) d[i] += d[i - x];  // 만들 수 있는 경우에만 채움
		}
	}
	return d[k];
}

// 물건을 한번씩만 쓰는 배낭 문제, 한개를 여러번 사용시는 M을 순방향으로 돌리면 됨.

/* 
D[i][j] = min(D[i - 1][j], D[i - 1][j - w[i]] + v[i]) : [0, i]의 범위에서 무게 합이 j이하가 되도록 물건을 골랐을 때 가치 합의 최대값
 */
int N, M;
ll dp[10001], W[101], V[101];
void solve() {
   cin >> N >> M;
   for (int i = 0; i < N; i++)
      cin >> W[i] >> V[i];
   for (int i = 0; i < N; i++)
      for (int j = M; j >= W[i]; j--)
         dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
   cout << dp[M];
}