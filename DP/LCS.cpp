#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

using vi = vector<int>;
template <typename T>
using wector = vector<vector<T>>;

// Get LCS length
int LCS(string& a,string& b,const int sz = 1000){
	const int aSz = a.size();
	const int bSz = b.size();
	wector<int> d(sz + 1,vector<int>(sz + 1, 0));
	for(int i = 1; i <= aSz; i++) for(int j = 1; j <= bSz; j++){
		if(a[i - 1] == b[j - 1]) d[i][j] = d[i - 1][j - 1] + 1;
		else d[i][j] = max(d[i - 1][j], d[i][j - 1]);
	}
	return d[aSz][bSz];
}