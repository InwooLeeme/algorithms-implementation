#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define pb push_back
#define si(x) (int)x.size()

const int SZ = 500 + 1;
struct GeneralMatching{
    int vis[SZ], par[SZ], orig[SZ], match[SZ], aux[SZ], t, N;
    vector<int> g[SZ];
    queue<int> q;

    void add_edge(int a, int b){
        g[a].push_back(b); g[b].push_back(a);
    }

    void init(int n){
        N = n; t = 0;
        for(int i = 0; i <= n; i++){
            g[i].clear();
            match[i] = aux[i] = par[i] = 0;
        }
    }

    void argument(int a, int b){
        int pv = b,nv;
        do{
            pv = par[b]; nv = match[pv];
            match[b] = pv; match[pv] = b;
            b = nv;
        } while(a != pv);
    }

    int lca(int a, int b){
        ++t;
        while(1){
            if(a){
                if(aux[a] == t) return a; aux[a] = t;
                a = orig[par[match[a]]];
            }
            swap(a, b);
        }
    }

    void blossom(int v, int w, int a){
        while(orig[v] != a){
            par[v] = w; w = match[v];
            if(vis[w] == 1) q.push(w), vis[w] = 0;
            orig[v] = orig[w] = a;
            v = par[w];
        }
    }

    bool bfs(int u){
        fill(vis + 1, vis + N + 1, -1);
        iota(orig + 1, orig + N + 1, 1);
        q = queue<int>(); q.push(u); vis[u] = 0;
        while(q.size()){
            auto v = q.front(); q.pop();
            for(int x : g[v]){
                if(vis[x] == -1){
                    par[x] = v; vis[x] = 1;
                    if(!match[x]) return argument(u, x), true;
                    q.push(match[x]); vis[match[x]] = 0;
                }
                else if(vis[x] == 0 and orig[v] != orig[x]){
                    int a = lca(orig[v], orig[x]);
                    blossom(x, v, a); blossom(v, x, a);
                }
            }
        }
        return false;
    }

    int Match(){
        int res = 0;
        vector<int> V(N, 0); iota(V.begin(), V.end(), 1);
        shuffle(V.begin(), V.end(), mt19937(0x94949));
        for(auto x : V) if(!match[x]){
            for(auto y : g[x]) if(!match[y]){
                match[x] = y; match[y] = x;
                res++; break;
            }
        }
        for(int i = 1; i <= N; i++) if(!match[i] and bfs(i)) res++;
        return res;
    }
};

// https://www.acmicpc.net/problem/13447

auto sol = [](){
    int n,m; cin >> n >> m;
    if(n & 1){
        cout << 0 << "\n";
        return;
    }
    GeneralMatching g;
    g.init(n);
    for(int _  = 0; _ < m; _++){
        int a,b; cin >> a >> b;
        g.add_edge(a, b);
    }
    int r = g.Match();
    cout << (r == (n / 2)) << "\n";
};

int32_t main(){
    cin.tie(0)->sync_with_stdio(0); 
    sol();
    return 0;
}
