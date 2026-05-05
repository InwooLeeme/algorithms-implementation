#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n, LOG;
    vector<int> tree;
    Fenwick(int n) : n(n), tree(n + 1, 0) {
        LOG = 0;
        while ((1 << (LOG + 1)) <= n) LOG++;
    }
    void update(int i, int v) {
        for (; i <= n; i += i & -i) tree[i] += v;
    }
    // prefix sum이 k에 도달하는 가장 왼쪽 위치 (1-indexed)
    int kth(int k) {
        int pos = 0;
        for (int pw = 1 << LOG; pw > 0; pw >>= 1) {
            if (pos + pw <= n && tree[pos + pw] < k) {
                pos += pw;
                k -= tree[pos];
            }
        }
        return pos + 1;
    }
};

int main(){
    cin.tie(0)->sync_with_stdio(0);
}
