#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

/* 
reference : https://ohgym.tistory.com/19
*/

// mobius function : 제곱 인수가 있는 정수인지, 없다면 소인수의 개수가 짝수인지 또는 홀수인지에 따라 {0, -1, 1}을 반환
vector<int> buildMu(const int sz){
	vector<int> mu(sz + 1, 0);
	mu[1] = 1;
	for(int i = 1; i <= sz; i++){
		for(int j = 2 * i; j <= sz; j += i){
			mu[j] -= mu[i];
		}
	}
	return mu;
}
int SFI(int n,const vector<int>& mu){ // find number of sqrt free : 제곱 인수가 없는 수들의 갯수 카운트
	int ret = 0;
	for(int i = 1; i * i <= n; i++) ret += mu[i] * (n / (i * i));
	return ret;
}