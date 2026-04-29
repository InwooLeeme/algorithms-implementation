template<typename T = int>
struct MergeSortTree {
    int sz;
    vector<vector<T>> tree;

    // constructor
    MergeSortTree(int n) {
        sz = 1;
        while (sz < n) sz <<= 1;
        tree.resize(sz << 1);
    }

    /* Start Base Method */
    // 1-indexed base
    void Add(int x, T v) {
        x += sz - 1; 
        tree[x].push_back(v);
    }

    // 0-indexed로 들어오는 표준 vector를 1-based 세그먼트 트리에 구축합니다.
    void Construct(const vector<T>& v) {
        const int n = v.size();
        for(int i = 0; i < n; i++) {
            Add(In[i + 1], v[i]); 
        }
        for(int i = sz - 1; i > 0; i--) {
            tree[i].resize(tree[i*2].size() + tree[i*2+1].size());
            merge(tree[i*2].begin(), tree[i*2].end(), 
                  tree[i*2+1].begin(), tree[i*2+1].end(), 
                  tree[i].begin());
        }
    }
    /* End Base Method */

    T Query(int L, int R, int k, int nodeNum, int nodeL, int nodeR) {
        if(R < nodeL || nodeR < L) return 0;
        if(L <= nodeL && nodeR <= R) {
            return upper_bound(tree[nodeNum].begin(), tree[nodeNum].end(), k) - tree[nodeNum].begin();
        }
        int mid = (nodeL + nodeR) >> 1;
        return Query(L, R, k, nodeNum * 2, nodeL, mid) + Query(L, R, k, nodeNum * 2 + 1, mid + 1, nodeR);
    }

    // [l, r] 범위 내에서 k 이하인 원소의 개수를 찾습니다. (l, r은 1-based)
    T Query(int l, int r, int k) {
        return Query(l, r, k, 1, 1, sz);
    }
};
