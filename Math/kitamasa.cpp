#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t

/*
kitamasa
ref : https://justicehui.github.io/hard-algorithm/2021/03/13/kitamasa/

https://www.acmicpc.net/problem/17272
17272 AC Code
*/

using poly = vector<int>;

constexpr int MOD = 1e9 + 7;

struct {
    static int Mod(int x) {
        x %= MOD;
        return x < 0 ? x + MOD : x;
    }
    poly Mul(const poly& a, const poly& b) {
        poly ret(a.size() + b.size() - 1);
        for (int i = 0; i < a.size(); i++) for (int j = 0; j < b.size(); j++) {
            ret[i + j] = (ret[i + j] + a[i] * b[j]) % MOD;
        }
        return ret;
    }
    poly Div(const poly& a, const poly& b) {
        poly ret(a.begin(), a.end());
        for (int i = ret.size() - 1; i >= b.size() - 1; i--) for (int j = 0; j < b.size(); j++) {
            ret[i + j - b.size() + 1] = Mod(ret[i + j - b.size() + 1] - ret[i] * b[j]);
        }
        ret.resize(b.size() - 1);
        return ret;
    }
    int operator() (poly& c, poly& a, int n) {
        poly d = { 1 }, xn = { 0, 1 };
        poly f(c.size() + 1); f.back() = 1;
        for (int i = 0; i < c.size(); i++) f[i] = Mod(-c[i]);
        while (n) {
            if (n & 1) d = Div(Mul(d, xn), f);
            n >>= 1; xn = Div(Mul(xn, xn), f);
        }
        int ret = 0;
        for (int i = 0; i < a.size(); i++) ret = Mod(ret + a[i] * d[i]);
        return ret;
    }
} kitamasa;

int32_t main(){
    fastio;
    int n,m; cin >> n >> m;
    poly x(m); x[0] = x.back() = 1;
    poly ret(m, 1);
    cout << kitamasa(x, ret, n) << "\n";
    return 0;
}
