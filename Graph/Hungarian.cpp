template <typename T>
struct Hungarian {
    int n, m;
    vector<vector<T>> cost;
    vector<T> u, v;
    vector<int> p, way;
    Hungarian(int n, int m) : n(n), m(m), cost(n + 1, vector<T>(m + 1)) {}
    void add(int i, int j, T w) {
        cost[i][j] = w;
    }
    pair<T, vector<int>> solve() {
        T inf = numeric_limits<T>::max() / 4;
        u.assign(n + 1, 0);
        v.assign(m + 1, 0);
        p.assign(m + 1, 0);
        way.assign(m + 1, 0);
        for(int i = 1; i <= n; i++) {
            p[0] = i;
            int j0 = 0;
            vector<T> minv(m + 1, inf);
            vector<bool> used(m + 1, false);
            do{
                used[j0] = true;
                int i0 = p[j0], j1 = 0;
                T delta = inf;
                for(int j = 1; j <= m; j++) {
                    if (used[j]) continue;
                    T cur = cost[i0][j] - u[i0] - v[j];
                    if(cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if(minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
                for (int j = 0; j <= m; j++) {
                    if (used[j]){
                        u[p[j]] += delta;
                        v[j] -= delta;
                    }else {
                        minv[j] -= delta;
                    }
                }
                j0 = j1;
            } while(p[j0] != 0);
            do{
                int j1 = way[j0];
                p[j0] = p[j1];
                j0 = j1;
            }while (j0);
        }
        vector<int>match(n + 1);
        for (int j = 1; j <= m; j++) {
            if(p[j]) match[p[j]] = j;
        }
        T ret = 0;
        for (int i = 1; i <= n; i++) ret += cost[i][match[i]];
        return {ret, match};
    }
};
