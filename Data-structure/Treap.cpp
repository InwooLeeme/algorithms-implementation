#include <bits/stdc++.h>
using namespace std;

struct Treap {
    struct Node {
        int key, pri, sz;
        Node *l, *r;
        Node(int k, int p) : key(k), pri(p), sz(1), l(nullptr), r(nullptr) {}
    };
    
    Node* root = nullptr;
    mt19937 rng{(unsigned)chrono::steady_clock::now().time_since_epoch().count()};
    
    int sz(Node* n) { return n ? n->sz : 0; }
    void pull(Node* n) { if (n) n->sz = 1 + sz(n->l) + sz(n->r); }
    
    void split(Node* n, int key, Node*& l, Node*& r) {
        if (!n) { l = r = nullptr; return; }
        if (n->key < key) { split(n->r, key, n->r, r); l = n; }
        else { split(n->l, key, l, n->l); r = n; }
        pull(n);
    }
    
    Node* merge(Node* a, Node* b) {
        if (!a) return b;
        if (!b) return a;
        if (a->pri > b->pri) { a->r = merge(a->r, b); pull(a); return a; }
        else { b->l = merge(a, b->l); pull(b); return b; }
    }
    
    bool _find(Node* n, int x) {
        if (!n) return false;
        if (n->key == x) return true;
        return x < n->key ? _find(n->l, x) : _find(n->r, x);
    }
    
    int _kth(Node* n, int k) {
        int ls = sz(n->l);
        if (k <= ls) return _kth(n->l, k);
        if (k == ls + 1) return n->key;
        return _kth(n->r, k - ls - 1);
    }
    
    int _order(Node* n, int x) {
        if (!n) return 0;
        if (n->key < x) return sz(n->l) + 1 + _order(n->r, x);
        return _order(n->l, x);
    }
    
    // x를 삽입. 이미 있으면 무시 (중복 허용 X, set처럼 동작)
    // 사용 예: tr.insert(5);
    void insert(int x) {
        if (_find(root, x)) return;
        Node *l, *r;
        split(root, x, l, r);
        root = merge(merge(l, new Node(x, rng())), r);
    }
    
    // x를 제거. 없으면 아무 것도 안 함
    // 사용 예: tr.erase(5);
    void erase(int x) {
        Node *l, *m, *r;
        split(root, x, l, r);
        split(r, x + 1, m, r);
        if (m) delete m;
        root = merge(l, r);
    }
    
    // x가 존재하는지 확인
    // 사용 예: if (tr.contains(5)) { ... }
    bool contains(int x) { return _find(root, x); }
    
    // k번째로 작은 원소 반환 (1-indexed)
    // 1 <= k <= size() 보장 필요. size() 초과 시 동작 정의 안 됨
    // 사용 예: int x = tr.kth(3);  // 3번째로 작은 값
    int kth(int k) { return _kth(root, k); }
    
    // x보다 작은 원소의 개수 (pbds의 order_of_key와 동일)
    // = x를 정렬된 위치에 삽입했을 때의 0-indexed 인덱스
    // 사용 예: int rank = tr.order_of_key(7);  // 7보다 작은 원소가 몇 개인지
    int order_of_key(int x) { return _order(root, x); }
    
    // 전체 원소 개수
    // 사용 예: if (tr.size() >= k) { ... }
    int size() { return sz(root); }
    
    // 비어있는지
    // 사용 예: if (!tr.empty()) { ... }
    bool empty() { return root == nullptr; }
};

int main() {
    Treap tr;
    
    tr.insert(10);
    tr.insert(5);
    tr.insert(20);
    tr.insert(15);
    tr.insert(7);
    
    cout << tr.size() << "\n";              // 5
    cout << tr.kth(1) << "\n";              // 5  (가장 작은 원소)
    cout << tr.kth(3) << "\n";              // 10 (3번째로 작은 원소)
    cout << tr.order_of_key(10) << "\n";    // 2  (10보다 작은 원소 개수: 5, 7)
    cout << tr.order_of_key(11) << "\n";    // 3  (11보다 작은 원소 개수: 5, 7, 10)
    cout << tr.contains(15) << "\n";        // 1
    
    tr.erase(10);
    cout << tr.kth(3) << "\n";              // 15 (10이 빠졌으니 3번째는 15)
}
