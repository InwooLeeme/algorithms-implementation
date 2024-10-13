struct Line {
	mutable ll a, b, p;
	bool operator<(const Line& i) const { return a < i.a; }
	bool operator<(ll x) const { return p < x; }
};
// default upper hull if get lower hull ? x축 대칭으로 넣어주기 y = ax + b -> y = -ax - b
struct LineContainer : multiset<Line, less<>> { 
	static constexpr ll INF = LLONG_MAX;
	ll Div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b != 0); }
	bool Cross(iterator x, iterator y) {
		if (y == end()) return x->p = INF, 0;
		if (x->a == y->a) x->p = x->b > y->b ? INF : -INF;
		else x->p = Div(y->b - x->b, x->a - y->a);
		return x->p >= y->p;
	}
	void Insert(ll a, ll b) { // y = ax + b
		auto z = insert({ a, b, 0 }), y = z++, x = y;
		while (Cross(y, z)) z = erase(z);
		if (x != begin() && Cross(--x, y)) Cross(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) Cross(x, erase(y));
	}
	ll Query(ll x) {
		auto l = *lower_bound(x);
		return l.a * x + l.b;
	}
} CHT;
