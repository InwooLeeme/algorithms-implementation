template <int K = 26, char BASE = 'a'>
struct MultisetHash {
    vector<ull> pre;

    static const ull* val() {
        static ull v[K];
        static bool done = false;
        if (!done) {
            mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
            for (int i = 0; i < K; i++) v[i] = rng();
            done = true;
        }
        return v;
    }

    MultisetHash(const string& s) : pre(s.size() + 1, 0) {
        const ull* v = val();
        for (size_t i = 0; i < s.size(); i++) pre[i + 1] = pre[i] + v[s[i] - BASE];
    }

    ull get(int l, int r) const { return pre[r] - pre[l]; }  // [l, r)
    int size() const { return (int)pre.size() - 1; }
};

// ===== 검색 템플릿 =====
// a, b에서 길이 L인 구간 중 구성이 같은 쌍이 있는지: O((N+M) log N)
template <int K, char BASE>
bool existsLen(const MultisetHash<K, BASE>& a, const MultisetHash<K, BASE>& b, int L) {
    vector<ull> v;
    for (int i = 0; i + L <= a.size(); i++) v.push_back(a.get(i, i + L));
    sort(v.begin(), v.end());
    for (int j = 0; j + L <= b.size(); j++)
        if (binary_search(v.begin(), v.end(), b.get(j, j + L))) return true;
    return false;
}

// 구성이 같은 구간 쌍의 최대 길이 (없으면 0). 단조성이 없어서 긴 길이부터 전부 확인한다.
template <int K, char BASE>
int longestCommon(const MultisetHash<K, BASE>& a, const MultisetHash<K, BASE>& b) {
    for (int L = min(a.size(), b.size()); L >= 1; L--)
        if (existsLen(a, b, L)) return L;
    return 0;
}
