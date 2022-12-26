#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

#define int int64_t

constexpr int sz = 1e7;
vector<int> p;
int sieve[sz + 1];

/* 
reference : https://rebro.kr/96
1. 각 2부터 n까지의 자연수 k에 대해, "k가 갖는 가장 작은 소인수"를 계산하는 방법
*/

/*
2. 각 2부터 n까지의 자연수 k에 대해, "빠르게 k를 소인수분해" 하는 방법
Factorize 메소드 참고
time : O(logK)
*/

constexpr int sz = 10'000'000;

// Sieve
vector<bool> p(sz, 1);
	p[1] = 0;
	for(int i = 2; i * i < sz; i++){
		for(int j = 2; i * j < sz; j++) p[i * j] = 0;
	}
	vector<int> v;
	for(int i = 2; i < sz; i++) if(p[i]) v.push_back(i);

// 1
int min_fact[sz + 1]; // i의 가장 작은 소인수

void Sieve(){
    for (int i = 0; i <= sz; i++) min_fact[i] = i;
	for (int i = 2; i <= sqrt(sz); i++) {
		if (min_fact[i] != i) continue;
		for (int j = i * i; j <= sz; j += i) {
			min_fact[j] = i;
		}
	}
}

// 2

vector<int> SieveWithFactorize(int x){
    vector<int> ret;
    while(min_fact[x] > 1){
        ret.push_back(min_fact[x]);
        x /= min_fact[x];
    }
    sort(ret.begin(), ret.end());
    return ret;
}



/* 
3. 약수의 개수 전처리
time : O(NlogN)
*/

vector<int> CountOfDivisor(){
    vector<int> fac(sz + 1, 0);
    for(int i = 1; i <= sz; i++){
        for(int j = i; j <= sz; j += i){
            fac[j]++;
        }
    }
    return fac;
}

int32_t main(){
    fastio;

}
