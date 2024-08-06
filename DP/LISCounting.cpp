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

const int PRECISION = 0;

/*
https://www.acmicpc.net/problem/17409
AC Code
위의 문제는 K = 3일때의 경우 
*/

constexpr int MOD = int(1e9) + 7;

struct Fenwick{
    vector<int> tree;
    int sz;
    Fenwick(int sz):tree(sz + 1), sz(sz){}
    void Update(int i, int val){
        for(; i <= sz; i += i & -i) if((tree[i] += val) >= MOD) tree[i] -= MOD;
    }
    int Query(int i){
        int ret = 0;
        for(; i; i -= i & -i) if((ret += tree[i]) >= MOD) ret -= MOD;
        return ret;
    }
};

void Main(){
    int n,k; cin >> n >> k; // k는 알아서 조정.
    // O(NlogN) DP[i][j] : i에서 끝나는 길이 j인 LIS의 개수 DP[i][j] = DP[k][j - 1](단, v[k] < v[i])
    // DP[k][j - 1]들의 합을 빠르게 구하기 위해 DP배열의 정의를 조금 바꿔서 D[v[i]][j]에 i에서 끝나는 길이 j인 LIS의 개수를 저장, k < v[j]인 DP[k][j - 1]의 합을 세그먼트 트리로 계산
    vector<Fenwick> v(k, Fenwick(n));   
    for(int i = 0; i < n; i++){
        int t; cin >> t; v[0].Update(t, 1);
        for(int j = 1; j < k; j++) v[j].Update(t, v[j - 1].Query(t - 1));
    }
    cout << v[k - 1].Query(n) << "\n";
}   

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed); cout.precision(PRECISION);
    Main();
    return 0;
}
