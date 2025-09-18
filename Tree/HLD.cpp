// ===== Heavy-Light Decomposition (Node/Edge 둘 다 지원) =====
// 기본 집계: 최대값, 항등원: -INF
// - 정점 세그트리: segNode  (pos[v] = in[v] 에 정점값 저장)
// - 간선 세그트리: segEdge  (pos[child] = in[child] 에 (parent,child) 간선값 저장)
// 쿼리
//   queryPathNode(u,v) : u~v 경로 정점 집계
//   queryPathEdge(u,v) : u~v 경로 간선 집계  ← ★ 오프바이원 안전
// 갱신
//   updateNode(v, val)      : 정점 v 값 변경
//   updateEdge(u,v, val)    : 간선(u,v) 값 변경 (더 깊은 쪽에 쓴다)

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NINF = (ll)-4e18;
const int PINF = (ll)4e18;

struct Seg {
    int n;
    vector<ll> t;
    static inline ll ID(){ return NINF; }           // 항등원
    static inline ll comb(ll a, ll b){ return max(a,b); } // 집계 연산

    Seg(){}
    Seg(int n): n(1){ while(this->n < n) this->n <<= 1; t.assign(this->n<<1, ID()); }
    void assignN(int n_){ n=1; while(n<n_) n<<=1; t.assign(n<<1, ID()); }
    void pointUpdate(int p, ll v){ // 1-indexed pos
        int i = (p-1) + n; t[i] = v;
        for(i >>= 1; i; i >>= 1) t[i] = comb(t[i<<1], t[i<<1|1]);
    }
    ll rangeQuery(int l, int r){ // 1-indexed inclusive
        if(l>r) return ID();
        ll L = ID(), R = ID();
        int i = (l-1) + n, j = (r-1) + n;
        while(i<=j){
            if(i&1) L = comb(L, t[i++]);
            if(!(j&1)) R = comb(t[j--], R);
            i >>= 1; j >>= 1;
        }
        return comb(L,R);
    }
};

struct HLD {
    int N, root, timer;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, in, out, sz;

    Seg segNode, segEdge; // 정점/간선용 세그트리

    HLD(int n=0){ init(n); }
    void init(int n){
        N=n; adj.assign(N+1,{});
        parent.assign(N+1,0); depth.assign(N+1,0);
        heavy.assign(N+1,-1); head.assign(N+1,0);
        in.assign(N+1,0); out.assign(N+1,0); sz.assign(N+1,0);
        timer=0;
    }
    void addEdge(int u,int v){ adj[u].push_back(v); adj[v].push_back(u); }

    int dfs1(int v,int p){
        parent[v]=p; sz[v]=1; int mx=0;
        for(int &to: adj[v]) if(to!=p){
            depth[to]=depth[v]+1;
            int s = dfs1(to,v);
            sz[v]+=s;
            if(s>mx) mx=s, heavy[v]=to;
        }
        return sz[v];
    }
    void dfs2(int v,int h){
        head[v]=h; in[v]=++timer;
        if(heavy[v]!=-1) dfs2(heavy[v], h);
        for(int to: adj[v]){
            if(to==parent[v] || to==heavy[v]) continue;
            dfs2(to,to);
        }
        out[v]=timer;
    }
    void build(int r=1){
        root=r; timer=0;
        dfs1(root,0);
        dfs2(root,root);
        segNode.assignN(N);
        segEdge.assignN(N); // edge는 in[child]에 저장할 것
    }

    // ----- 갱신 -----
    void updateNode(int v, ll val){ segNode.pointUpdate(in[v], val); }
    // 간선(u,v) 갱신: 더 깊은 쪽의 in[] 위치에 기록
    void updateEdge(int u,int v,ll val){
        if(parent[u]==v) segEdge.pointUpdate(in[u], val);
        else if(parent[v]==u) segEdge.pointUpdate(in[v], val);
        else {
            // u-v가 직접 간선이 아닌 경우: LCA경로의 특정 간선을 바꾸려는 게 아니라면 사용 X
            // 필요 시 별도 처리
            assert(false && "updateEdge: (u,v) is not a tree edge");
        }
    }

    // ----- 쿼리: 경로 상 정점 집계 -----
    ll queryPathNode(int u,int v){
        ll res = Seg::ID();
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]]) swap(u,v);
            res = Seg::comb(res, segNode.rangeQuery(in[head[u]], in[u]));
            u = parent[head[u]];
        }
        if(in[u]>in[v]) swap(u,v);
        res = Seg::comb(res, segNode.rangeQuery(in[u], in[v]));
        return res;
    }

    // ----- 쿼리: 경로 상 간선 집계 (★오프바이원 처리 포함) -----
    // segEdge는 pos[child]=in[child]에 (parent,child) 간선값 저장
    ll queryPathEdge(int u,int v){
        ll res = Seg::ID();
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]]) swap(u,v);
            // 체인 [head[u]..u] 내 간선만: in[head[u]]+1 ~ in[u]
            res = Seg::comb(res, segEdge.rangeQuery(in[head[u]], in[u]));
            u = parent[head[u]];
        }
        if(in[u]>in[v]) swap(u,v);
        // 같은 체인 마무리: 간선이므로 [in[u]+1, in[v]]
        res = Seg::comb(res, segEdge.rangeQuery(in[u]+1, in[v]));
        return res;
    }

    // (옵션) 서브트리 쿼리/갱신은 "정점 저장"에서만 의미가 있다.
    ll querySubtreeNode(int v){ return segNode.rangeQuery(in[v], out[v]); }
    void updateSubtreeNode(int v, ll val){ // 예: 전부 세팅하려면 lazy seg 필요
        segNode.pointUpdate(in[v], val); // point만 예시
    }

    // 유용 보조
    int lca(int a,int b){
        while(head[a]!=head[b]){
            if(depth[head[a]]>depth[head[b]]) a=parent[head[a]];
            else b=parent[head[b]];
        }
        return (in[a]<in[b]?a:b);
    }
};
