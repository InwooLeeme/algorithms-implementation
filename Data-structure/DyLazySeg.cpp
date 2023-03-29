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
BOJ 10999 구간 합 구하기 AC Code
using dynamic Lazy Segment Tree
Ref : https://www.acmicpc.net/source/share/555975fefd344c3ead103392e81acc24 ( GOD )
ToDo : 혼자 안보고 짤 수 있을때까지 숙달하기..
1 BASE Update, Query
Update, Query쪽 s,e @par는 입력으로 들어오는 범위에 따라서 조절 10999번에선 (1 ≤ N ≤ 1,000,000)
*/

struct Node{
    int v,lazy;
    Node *l, *r;
    Node():l(nullptr),r(nullptr),v(0),lazy(0){}
    void Push(int s,int e){
        if(!lazy) return;
        v += lazy * (e - s + 1);
        if(s == e){ lazy = 0; return; }
        int mid = s + e >> 1;
        if(!l) l = new Node();
        if(!r) r = new Node();
        l->lazy += lazy; r->lazy += lazy;
        lazy = 0;
    }
};

void Update(Node* nd, int l, int r, int k, int s = 1, int e = 1e9){
    nd->Push(s, e);
    if(r < s || e < l) return;
    if(l <= s and e <= r){
        nd->lazy += k; nd->Push(s, e);
        return;
    }
    int mid = s + e >> 1;
    if(!nd->l) nd->l = new Node();
    if(!nd->r) nd->r = new Node();
    Update(nd->l, l, r, k, s, mid);
    Update(nd->r, l, r, k, mid + 1, e);
    nd->v = nd->l-> v + nd->r->v;
}

int Query(Node* nd, int l, int r, int s = 1, int e = 1e9){
    if(!nd) return 0;
    nd->Push(s, e);
    if(r < s || e < l) return 0;
    if(l <= s and e <= r) return nd->v;
    int mid = s + e >> 1;
    return Query(nd->l, l, r, s, mid) + Query(nd->r, l, r, mid + 1, e);
}

int32_t main(){
    fastio;
    int n,m,k; cin >> n >> m >> k;
    Node* root = new Node();
    for(int i = 1,t; i <= n; i++){
        cin >> t;
        Update(root, i, i, t);
    }
    for(int i = 0; i < m + k; i++){
        int t,a,b,c; cin >> t >> a >> b;
        if(t == 1) cin >> c,Update(root, a, b, c);
        else if(t == 2) cout << Query(root, a, b) << "\n";
    }
    return 0;
}
