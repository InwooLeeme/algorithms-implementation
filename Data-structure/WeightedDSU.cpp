struct WeightedDSU {
    vector<int> p, r;
    vector<int> d;
    WeightedDSU(int n = 0) { build(n); }
    void build(int n){
        p.resize(n + 1);
        r.assign(n + 1, 0);
        d.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) p[i] = i;
    }
    int Find(int x) {
        if (p[x] == x) return x;
        int px = p[x];
        p[x] = Find(px);
        d[x] += d[px];
        return p[x];
    }
	int w(int x) {
        Find(x);
        return d[x];
    }
    bool Union(int a, int b, int wdiff) {
        int ra = Find(a), rb = Find(b);
    	int wa = w(a), wb = w(b);
        if (ra == rb) return (wa - wb == wdiff);
    	int rdiff = wdiff - wa + wb;
        if (r[ra] < r[rb]) {
            p[ra] = rb;
            d[ra] = rdiff;
        } 
		else{
            p[rb] = ra;
            d[rb] = -rdiff;
            if (r[ra] == r[rb]) r[ra]++;
        }
        return 1;
    }
};
