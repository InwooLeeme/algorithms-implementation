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
1. 각 2부터 n까지의 자연수 k에 대해, "k가 갖는 가장 작은 소인수"를 계산하는 방법
 */
void Sieve(){
    for(int i = 1; i <= sz; i++) sieve[i] = i;
    for(int i = 1; i <= sz; i++){
        if(sieve[i] == i){ // 아직 걸러지지 않음. i는 prime number
            for(int j = 2; j * i <= sz; j++){
                if(sieve[i * j] == i * j) sieve[i * j] = i;
            }
            p.push_back(i);
        }
    }
}

/* 
2. 각 2부터 n까지의 자연수 k에 대해, "빠르게 k를 소인수분해" 하는 방법
time : O(logK)
 */
vector<int> FactorizeSieve(int x){
    vector<int> ret;
    while(x){
        ret.push_back(sieve[x]);
        x /= sieve[x];
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