// Binary lifting / `Doubling`
// Complexity: O(NlogN) precalculation / O(logN) per query
// <https://atcoder.jp/contests/arc060/submissions/7039451>
struct BinaryLifting {
    int N, INVALID, lgD;
    std::vector<std::vector<int>> mat;
    BinaryLifting() : N(0), lgD(0) {}
    BinaryLifting(const std::vector<int> &vec_nxt, int INVALID = -1, int lgd = 0)
        : N(vec_nxt.size()), INVALID(INVALID), lgD(lgd) {
        while ((1LL << lgD) < N) lgD++;
        mat.assign(lgD, std::vector<int>(N, INVALID));
        mat[0] = vec_nxt;
        for (int i = 0; i < N; i++)
            if (mat[0][i] < 0 or mat[0][i] >= N) mat[0][i] = INVALID;
        for (int d = 0; d < lgD - 1; d++) {
            for (int i = 0; i < N; i++)
                if (mat[d][i] != INVALID) mat[d + 1][i] = mat[d][mat[d][i]];
        }
    }
    int kth_next(int now, long long k) {
        if (k >= (1LL << lgD)) exit(8);
        for (int d = 0; k and now != INVALID; d++, k >>= 1)
            if (k & 1) now = mat[d][now];
        return now;
    }

    // Distance from l to [r, \infty)
    // Requirement: mat[0][i] > i for all i (monotone increasing)
    int distance(int l, int r) {
        if (l >= r) return 0;
        int ret = 0;
        for (int d = lgD - 1; d >= 0; d--) {
            if (mat[d][l] < r and mat[d][l] != INVALID) ret += 1 << d, l = mat[d][l];
        }
        if (mat[0][l] == INVALID or mat[0][l] >= r)
            return ret + 1;
        else
            return -1; // Unable to reach
    }
};
// using
// Problem url : https://atcoder.jp/contests/abc367/tasks/abc367_e
int main() {
    int N;
    lint K;
    cin >> N >> K;
    vector<int> X(N), A(N);
    cin >> X >> A;
    for (auto &x : X) --x;

    vector<int> nxt(N);
    REP(i, N) nxt.at(i) = X.at(i);
    BinaryLifting bl(nxt, -1, 60);
    REP(i, N) {
        cout << A.at(bl.kth_next(i, K)) << ' ';
    }
    cout << endl;
}
