#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t

/*
GaussElimination
BOJ 22940 AC Code
https://www.acmicpc.net/problem/22940
*/

const int PRECISION = 0;

template<typename T>
struct GaussElimination { // reference : https://blog.naver.com/jhnah917/222529605959
    using row = vector<T>;
    using matrix = vector<row>;

    template<enable_if_t<is_arithmetic_v<T>>* = nullptr>
    static bool IsZero(T val) {
        if constexpr (is_integral<T>::value) return val == 0;
        else return abs(val) < 1e-9;
    }

    template<bool IsSquare = 1>
    static tuple<matrix, T, T, matrix> Gauss(matrix v) { // return { rref, rank, det, inv }
        const int n = v.size(), m = v[0].size(); int rank = 0;
        matrix inv(n, row(m)); T det = 1;
        for (int i = 0; i < n; i++) if (IsSquare) inv[i][i] = 1;
        for (int j = 0; j < m && rank < n; j++) {
            if (IsZero(v[rank][j])) {
                T mx = 0; int idx = -1;
                for (int i = rank + 1; i < n; i++) if (mx < abs(v[i][j])) mx = abs(v[i][j]), idx = i;
                if (idx == -1 || IsZero(mx)) { det = 0; continue; }
                for (int k = 0; k < m; k++) {
                    v[rank][k] += v[idx][k];
                    if (IsSquare) inv[rank][k] += inv[idx][k];
                }
            }
            const T coeff = 1 / v[rank][j]; det *= v[rank][j];
            for (int k = 0; k < m; k++) {
                v[rank][k] *= coeff;
                if (IsSquare) inv[rank][k] *= coeff;
            }
            for (int i = 0; i < n; i++) {
                if (rank == i) continue;
                const T t = v[i][j];
                for (int k = 0; k < m; k++) {
                    v[i][k] -= v[rank][k] * t;
                    if (IsSquare) inv[i][k] -= inv[rank][k] * t;
                }
            }
            rank++;
        }
        return { v, rank, det, inv };
    }
};

using G = GaussElimination<double>;

void Sol(){
    int n; cin >> n; 
    G::matrix v(n, G::row(n + 1));
    for(int i = 0; i < n; i++) for(int j = 0; j <= n; j++) cin >> v[i][j];
    auto rett = get<0>(G::Gauss<0>(v));
    for(auto& i : rett) cout << (int)(round(i.back())) << " ";
    cout << "\n";
}

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed); cout.precision(PRECISION);
    Sol();
    return 0;
}
