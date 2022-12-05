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

2. 각 2부터 n까지의 자연수 k에 대해, "빠르게 k를 소인수분해" 하는 방법
Factorize 메소드 참고
time : O(logK)
 */
template<size_t sz = 100'000>
struct LinearSieve {
	vector<int> p;
	int sieve[sz + 1]; // sieve[i] : IsPrime(i) ? 0 : smallest prime factor
	int d[sz + 1]; // for factorize
	LinearSieve() : sieve{} {
		sieve[0] = sieve[1] = -1;
		for (int i = 2; i <= sz; i++) {
			if (!sieve[i]) p.push_back(i);
			for (auto j : p) {
				if (i * j > sz) break;
				sieve[i * j] = j;
				d[i * j] = i;
				if (i % j == 0) break;
			}
		}
	}
	bool IsPrime(int n) { return !sieve[n]; }
	vector<int> Factorize(int t){ 
		vector<int> ret;
		while(sieve[t]){
			ret.push_back(sieve[t]);
			t /= d[t];
		}
		sort(ret.begin(), ret.end());
		return ret;
	}
}; LinearSieve Sieve;

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
