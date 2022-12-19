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
- 물건 수 N, 무게 제한 M
- v[i]에는 i번째 물건의 <무게, 가치>를 저장
*/
vector<vector<int>> dp;

void Sol(){
    int N, M; cin >> N >> M;

    vector<pair<int, int>> v(N+1); // <weight, value>
    for(int i=1; i<=N; i++)
        cin >> v[i].first >> v[i].second;

    dp.resize(N+1, vector<int>(M+1));

    for(int i=1; i<=N; i++)
        for(int j=1; j<=M; j++) {
            dp[i][j] = dp[i-1][j];
            if(v[i].first <= j)
                dp[i][j] = max(dp[i][j], dp[i-1][j - v[i].first] + v[i].second);
        }

    cout << dp[N][M] << "\n";

}
