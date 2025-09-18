// ===================== Universal HLD Template (C++17) =====================
// Features
//  - Node & Edge values 둘 다 지원
//  - Path/Subtree range add, range sum/max
//  - Point set/add, LCA, jump_up, kth_on_path(0-indexed)
//  - Off-by-one safe for edges: edge on child mapped at in[child]
//      * chain jump:      [in[head[u]], in[u]]
//      * same-chain tail: [in[u] + 1, in[v]]
// Indexing: vertices are 1-indexed
// ==========================================================================

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll NINF = (ll)-4e18;

struct LazySeg {
    struct Node {
        ll sum = 0;     // range sum
        ll mx  = NINF;  // range max
        int len = 0;    // number of positions in this segment
    };
    struct Tag { ll add = 0; }; // range add

    static Node merge(const Node& L, const Node& R){
        return Node{ L.sum + R.sum, max(L.mx, R.mx), L.len + R.len };
    }
    static void apply(Node& nd, const Tag& tg){
        if(nd.len==0) return;
        nd.sum += tg.add * nd.len;
        if (nd.mx != NINF) nd.mx += tg.add; // keep -INF for empty
    }
    static void compose(Tag& cur, const Tag& add){ cur.add += add.add; }

    int n;                   // power-of-two size
    vector<Node> st;
    vector<Tag>  lz;

    LazySeg(): n(0) {}
    void init(int N){        // build as all zeros
        n=1; while(n<N) n<<=1;
        st.assign(n<<1, Node{0, NINF, 0});
        lz.assign(n<<1, Tag{0});
        for(int i=n; i<n+N; ++i) st[i].len = 1;
        for(int i=n-1; i>=1; --i) st[i].len = st[i<<1].len + st[i<<1|1].len;
    }
    // 1-indexed array A[1..N]
    void build_from(const vector<ll>& A){
        int N = (int)A.size()-1;
        init(N);
        for(int i=1;i<=N;i++) st[n-1+i] = Node{A[i], A[i], 1};
        for(int i=n-1;i>=1;--i) st[i] = merge(st[i<<1], st[i<<1|1]);
    }
    void push(int p){
        if(lz[p].add!=0){
            apply(st[p<<1],   lz[p]); compose(lz[p<<1],   lz[p]);
            apply(st[p<<1|1], lz[p]); compose(lz[p<<1|1], lz[p]);
            lz[p] = Tag{0};
        }
    }
    void pull(int p){ st[p] = merge(st[p<<1], st[p<<1|1]); }

    // range add on [l, r] (1-indexed, inclusive)
    void range_add(int l,int r,ll v){ range_add(l,r,v,1,1,n); }
    void range_add(int l,int r,ll v,int p,int L,int R){
        if(r<L || R<l) return;
        if(l<=L && R<=r){ apply(st[p], Tag{v}); compose(lz[p], Tag{v}); return; }
        push(p);
        int M=(L+R)>>1;
        range_add(l,r,v,p<<1,L,M);
        range_add(l,r,v,p<<1|1,M+1,R);
        pull(p);
    }
    ll range_sum(int l,int r){ return range_sum(l,r,1,1,n); }
    ll range_sum(int l,int r,int p,int L,int R){
        if(r<L || R<l) return 0;
        if(l<=L && R<=r) return st[p].sum;
        push(p);
        int M=(L+R)>>1;
        return range_sum(l,r,p<<1,L,M) + range_sum(l,r,p<<1|1,M+1,R);
    }
    ll range_max(int l,int r){ return range_max(l,r,1,1,n); }
    ll range_max(int l,int r,int p,int L,int R){
        if(r<L || R<l) return NINF;
        if(l<=L && R<=r) return st[p].mx;
        push(p);
        int M=(L+R)>>1;
        return max(range_max(l,r,p<<1,L,M), range_max(l,r,p<<1|1,M+1,R));
    }
    // point set: set position i to 'val' (via delta add)
    void point_set(int i, ll val){
        ll cur = range_sum(i,i);
        range_add(i,i, val - cur);
    }
};

struct HLD {
    int N, root, timer;
    vector<vector<int>> g;
    vector<int> parent, depth, heavy, head, in, out, sz, rid; // rid[in] = vertex

    LazySeg segNode, segEdge; // node/edge segment trees

    HLD(int n=0){ init(n); }
    void init(int n){
        N=n; root=1; timer=0;
        g.assign(N+1,{});
        parent.assign(N+1,0);
        depth.assign(N+1,0);
        heavy.assign(N+1,-1);
        head.assign(N+1,0);
        in.assign(N+1,0);
        out.assign(N+1,0);
        sz.assign(N+1,0);
        rid.assign(N+1,0);
    }
    void add_edge(int u,int v){ g[u].push_back(v); g[v].push_back(u); }

    int dfs1(int u,int p){
        parent[u]=p; sz[u]=1; int mx=0;
        for(int v: g[u]) if(v!=p){
            depth[v]=depth[u]+1;
            int s = dfs1(v,u);
            sz[u]+=s;
            if(s>mx) mx=s, heavy[u]=v;
        }
        return sz[u];
    }
    void dfs2(int u,int h){
        head[u]=h; in[u]=++timer; rid[timer]=u;
        if(heavy[u]!=-1) dfs2(heavy[u], h);
        for(int v: g[u]) if(v!=parent[u] && v!=heavy[u]) dfs2(v,v);
        out[u]=timer;
    }
    void build(int r=1){
        root=r; timer=0;
        dfs1(root,0); dfs2(root,root);
        segNode.init(N);   // 필요 시 build_from 사용
        segEdge.init(N);   // edge는 in[child]에 저장
    }

    // --------------------- Node values ---------------------
    void node_point_set(int u, ll val){ segNode.point_set(in[u], val); }
    void node_point_add(int u, ll delta){ segNode.range_add(in[u], in[u], delta); }

    void node_path_add(int u,int v,ll delta){
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]]) swap(u,v);
            segNode.range_add(in[head[u]], in[u], delta);
            u = parent[head[u]];
        }
        if(in[u]>in[v]) swap(u,v);
        segNode.range_add(in[u], in[v], delta);
    }
    ll node_path_sum(int u,int v){
        ll res=0;
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]]) swap(u,v);
            res += segNode.range_sum(in[head[u]], in[u]);
            u = parent[head[u]];
        }
        if(in[u]>in[v]) swap(u,v);
        res += segNode.range_sum(in[u], in[v]);
        return res;
    }
    ll node_path_max(int u,int v){
        ll res=NINF;
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]]) swap(u,v);
            res = max(res, segNode.range_max(in[head[u]], in[u]));
            u = parent[head[u]];
        }
        if(in[u]>in[v]) swap(u,v);
        res = max(res, segNode.range_max(in[u], in[v]));
        return res;
    }
    void node_subtree_add(int u,ll delta){ segNode.range_add(in[u], out[u], delta); }
    ll  node_subtree_sum(int u){ return segNode.range_sum(in[u], out[u]); }
    ll  node_subtree_max(int u){ return segNode.range_max(in[u], out[u]); }

    // --------------------- Edge values ---------------------
    // (u,v)가 "트리 간선"이어야 함. 더 깊은 쪽의 in[]에 저장.
    void edge_point_set(int u,int v,ll val){
        if(parent[u]==v) segEdge.point_set(in[u], val);
        else if(parent[v]==u) segEdge.point_set(in[v], val);
        else { assert(false && "edge_point_set: not a tree edge"); }
    }
    void edge_point_add(int u,int v,ll delta){
        if(parent[u]==v) segEdge.range_add(in[u], in[u], delta);
        else if(parent[v]==u) segEdge.range_add(in[v], in[v], delta);
        else { assert(false && "edge_point_add: not a tree edge"); }
    }
    // Path add/sum/max for edges (★ off-by-one handled)
    void edge_path_add(int u,int v,ll delta){
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]]) swap(u,v);
            segEdge.range_add(in[head[u]], in[u], delta); // chain jump: include head edge
            u = parent[head[u]];
        }
        if(in[u]>in[v]) swap(u,v);
        if(u!=v) segEdge.range_add(in[u]+1, in[v], delta); // same chain tail excludes LCA edge
    }
    ll edge_path_sum(int u,int v){
        ll res=0;
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]]) swap(u,v);
            res += segEdge.range_sum(in[head[u]], in[u]);
            u = parent[head[u]];
        }
        if(in[u]>in[v]) swap(u,v);
        if(u!=v) res += segEdge.range_sum(in[u]+1, in[v]);
        return res;
    }
    ll edge_path_max(int u,int v){
        ll res=NINF;
        while(head[u]!=head[v]){
            if(depth[head[u]]<depth[head[v]]) swap(u,v);
            res = max(res, segEdge.range_max(in[head[u]], in[u]));
            u = parent[head[u]];
        }
        if(in[u]>in[v]) swap(u,v);
        if(u!=v) res = max(res, segEdge.range_max(in[u]+1, in[v]));
        return res;
    }

    // --------------------- Helpers ---------------------
    int lca(int a,int b){
        while(head[a]!=head[b]){
            if(depth[head[a]]>depth[head[b]]) a=parent[head[a]];
            else b=parent[head[b]];
        }
        return (in[a]<in[b]?a:b);
    }
    // jump up by k edges from u (k>=0). O(#chains)
    int jump_up(int u, int k){
        while(u && k){
            int h = head[u];
            int d = depth[u] - depth[h];
            if(k <= d) return rid[in[u] - k];
            k -= d+1; u = parent[h];
        }
        return (k==0? u : 0); // 0 = invalid
    }
    // kth node on path u->v (0-indexed from u). returns 0 if k out of range.
    int kth_on_path(int u,int v,int k){
        int w = lca(u,v);
        int du = depth[u] - depth[w];
        if(k <= du) return jump_up(u, k);
        k -= du;
        int dv = depth[v] - depth[w];
        if(k > dv) return 0;
        return jump_up(v, dv - k);
    }
};

/*
------------------------------ Usage example ------------------------------
int n; cin>>n;
HLD h(n);
for(int i=0;i<n-1;i++){ int a,b; cin>>a>>b; h.add_edge(a,b); }
h.build(1); // root = 1 (changeable)

// Node initial values (optional):
//   vector<ll> base(n+1);
//   for(int v=1; v<=n; ++v) base[h.in[v]] = initValueOfNodeV;
//   h.segNode.build_from(base);

// Edge initial values (optional):
//   for(each tree edge (u,v)) h.edge_point_set(u,v, w);

// Queries/updates:
//   h.node_path_add(u,v,delta), h.node_path_sum(u,v), h.node_path_max(u,v)
//   h.node_subtree_add(u,delta), h.node_subtree_sum(u), h.node_subtree_max(u)
//   h.edge_path_add(u,v,delta), h.edge_path_sum(u,v), h.edge_path_max(u,v)
//   h.lca(u,v), h.kth_on_path(u,v,k)
*/
