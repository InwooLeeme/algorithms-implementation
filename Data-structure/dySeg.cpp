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
2042 AC Code
*/

struct node {
    int v, s, e;
    node *l, *r;
    node(int s, int e): v(0), s(s), e(e), l(0), r(0) {}
    void update(int k, int x) {
        if (s == e) { v = x; return; }
        int m = (s+e)>>1;
        if (k <= m) {
            if (!l) l = new node(s,m);
            l->update(k,x);
        } else {
            if (!r) r = new node(m+1,e);
            r->update(k,x);
        }
        v = (l?l->v:0) + (r?r->v:0);
    }
    int query(int a, int b) {
        if (a <= s and e <= b) return v;
        if (b < s or e < a) return 0;
        return (l?l->query(a,b):0) + (r?r->query(a,b):0);
    }
};

int32_t main(){
    fastio;
    int n,m,k; cin >> n >> m >> k;
    node *dst = new node(1, n);
    for(int i = 1; i <= n; i++){
        int t; cin >> t;
        dst->update(i, t);
    }
    for(int i = 0; i < m + k; i++){
        int t,a,b; cin >> t >> a >> b;
        if(t == 1){
            dst->update(a, b);
        }
        else cout << dst->query(a, b) << "\n";
    }
    return 0;
}
