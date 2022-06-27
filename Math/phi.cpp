#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

int phi(int n){ // ϕ(n) : n 이하의 양의 정수중 n과 서로소인 것의 개수
    int s = n;
    for(int i = 2; i * i <= n; i++)
    {
        if(n % i == 0)
        {
            while(n % i == 0)n /= i;
            s = s / i * (i - 1);
        }
    }
    if(n > 1)s = s / n * (n - 1);
    return s;
}