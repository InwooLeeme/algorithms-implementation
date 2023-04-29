# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")
# pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t

/*
BOJ 1179 AC Code
https://www.acmicpc.net/problem/1179
요세푸스 문제 점화식 및 구현법
https://en.wikipedia.org/wiki/Josephus_problem
*/

int n,k;
// O(N) : f(n,k) = (f(n - 1,k) + k) mod n
/*
for(int i = 0; i < n; i++){
    ret = (ret + k) % (i + 1);
}
*/

// O(KlogN) method
int f(int n){
    if(n == 1) return 0;
    if(k > n) return (f(n - 1) + k)% n; 
    int h = f(n - n / k) - (n % k);
    if(h < 0) return h + n;
    return h + h / (k - 1);
}

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> k;
    if(k == 1) cout << n << '\n';
    else cout << f(n) + 1 << '\n';
    return 0;   
}
