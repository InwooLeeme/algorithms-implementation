template <typename T>
struct Fenwick2D { // 1-indexed
    vector<vector<T>> data;
    int N, M;
    void init(int N, int M) { // Row: N / Column: M
        this->N = N;
        this->M = M;
        data.resize(N + 2);
        for(int i = 0; i < N + 2; ++i) {
            data[i].resize(M + 2);
            fill(data[i].begin(), data[i].end(), 0);
        }
    }
    void update(int r, int c, T v) {
        for(int cr = r; cr <= N; cr += cr & -cr) {
            for(int cc = c; cc <= M; cc += cc & -cc) {
                data[cr][cc] += v;
            }
        }
    }
    T get(int r, int c) {
        T res = 0;
        for(int cr = r; cr > 0; cr -= cr & -cr) {
            for(int cc = c; cc > 0; cc -= cc & -cc) {
                res += data[cr][cc];
            }
        }
        return res;
    }
};
