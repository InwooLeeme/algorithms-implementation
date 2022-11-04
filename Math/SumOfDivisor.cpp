#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

/* 
[0, sz]인 약수의 합 전처리 : O(NlogN)
 */
template<size_t sz = 100'000>
vector<int> sumDiv(){
    vector<int> sdiv(sz + 1, 0);
    for(int i = 1; i <= sz; i++){
        for(int j = i; j <= sz; j += i){
            sdiv[j] += i;
        }
    }
    return sdiv;
}

int main(){
    return 0;
}