#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

using ll = long long;
const int INF = int(1e9) + 7;

struct SplayTree {
    struct Node {
        //member variable
        Node* l, * r, * p;
        ll sz, v, sum, mx, mn;
        bool flip, dummy;
        //constructor, destructor
        Node(ll v = 0, Node* p = nullptr) : v(v), sum(v), mx(v), mn(v), p(p) {
            l = r = nullptr, sz = 1, flip = dummy = 0;
        }
        ~Node() { delete l; delete r; }
        //basic method
        bool IsLeft() const { return this == p->l; }
        void Rotate() {
            if (IsLeft()) r && (r->p = p), p->l = r, r = p;
            else l && (l->p = p), p->r = l, l = p;
            if (p->p) (p->IsLeft() ? p->p->l : p->p->r) = this;
            auto t = p; p = t->p; t->p = this;
            t->Update(); Update();
        }
        void Update() {
            sz = 1; sum = mn = mx = v;
            if (l) {
                sz += l->sz, sum += l->sum;
                mn = min(mn, l->mn), mx = max(mx, l->mx);
            }
            if (r) {
                sz += r->sz, sum += r->sum;
                mn = min(mn, r->mn), mx = max(mx, r->mx);
            }
        }
        void Push() {
            if (flip) {
                swap(l, r);
                if (l) l->flip ^= 1;
                if (r) r->flip ^= 1;
                flip = 0;
            }
        }
    };
    //member variable
    Node* root;
    Node* ptr[101010];
    //constructor, destructor
    SplayTree() : root() { memset(ptr, 0, sizeof ptr); }
    ~SplayTree() { if (root) delete root; }
    //basic method
    void Splay(Node* x, Node* p = nullptr) {
        for (; x->p != p; x->Rotate()) {
            if (x->p->p != p) x->p->p->Push(); x->p->Push(); x->Push();
            if (x->p->p != p) (x->IsLeft() ^ x->p->IsLeft() ? x : x->p)->Rotate();
        }
        if (!p) root = x; x->Push();
    }
    void Kth(int k) {
        auto cur = root; cur->Push();
        while (1) {
            while (cur->l && cur->l->sz > k) cur = cur->l, cur->Push();
            if (cur->l) k -= cur->l->sz;
            if (!k--) break;
            cur = cur->r; cur->Push();
        }
        Splay(cur);
    }
    Node* Gather(int l, int r) {
        Kth(r + 1); auto t = root;
        Kth(l - 1); Splay(t, root);
        return root->r->l;
    }
    //additional method
    void Init(int n) {
        if (root) delete root;
        root = new Node(-INF); root->dummy = 1;
        auto cur = root;
        for (int i = 1; i <= n; i++) {
            ptr[i] = cur->r = new Node(i, cur);
            cur = cur->r;
        }
        cur->r = new Node(INF, cur); cur->r->dummy = 1;
        for (int i = n; i >= 1; i--) ptr[i]->Update();
        Splay(ptr[n + 1 >> 1]);
    }
    void Print(Node* x) {
        x->Push();
        if (x->l) Print(x->l);
        if (!x->dummy) cout << x->v << ' ';
        if (x->r) Print(x->r);
    }
    void Flip(int l, int r) {
        auto t = Gather(l, r);
        t->flip ^= 1;
    }
    void Shift(int l, int r, int k) {
        Gather(l, r);
		k %= r - l + 1;
        if (k < 0) k += r - l + 1;
        if (k) Flip(l, r), Flip(l, l + k - 1), Flip(l + k, r);
    }
}tree;

int main(){
    fastio;

    return 0;
}