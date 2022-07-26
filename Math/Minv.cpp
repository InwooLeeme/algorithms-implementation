#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

constexpr int MOD = 1e9 + 7;

int minv(const int a, const int b = MOD) {
    if (a == 0 && b == 1) return 0;
    if (a == 1) return 1;
    return b - 1LL * minv(b % a, a) * b / a;
}

int32_t main(){
    fastio;

}