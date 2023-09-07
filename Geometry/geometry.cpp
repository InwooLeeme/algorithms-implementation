#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

#define int int_fast64_t
#define double long double
const double EPS = 1e-12;
const double PI = acos(-1);

struct point {
	int x, y;
	/* constructors */
	point() : x(0), y(0) {}
	point(int x, int y) : x(x), y(y) {}
	/* methods */
	friend int dist(point a, point b) { // (Euclidean distance)^2, use ll if x, y > 1e4
		return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	}
	friend int ccw(point a, point b, point c) {
		int t = (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
		return t ? t > 0 ? 1 : -1 : 0;
	}
	friend int is_cross(point a, point b, point c, point d) { // cross : -1(X), intersect : 1(X or L)
		int ab = ccw(a, b, c) * ccw(a, b, d);
		int cd = ccw(c, d, a) * ccw(c, d, b);
		if (ab < 0 && cd < 0) return -1;
		if (ab == 0 && cd == 0) {
			if (a > b) swap(a, b);
			if (c > d) swap(c, d);
			if (!ccw(a, b, c) and !ccw(a, b, d) and !ccw(c, d, a) and !ccw(c, d, b) and c < b and a < d) return 2; // intersect INF
			return c <= b && a <= d;
		}
		return ab <= 0 && cd <= 0;
	}
	friend point findInterCod(point a, point b, point c, point d){
		double x = (a.x*b.y - a.y*b.x)*(c.x - d.x) - (a.x - b.x) * (c.x*d.y - c.y*d.x);
		double y = (a.x*b.y - a.y*b.x)*(c.y - d.y) - (a.y - b.y) * (c.x*d.y - c.y*d.x);
		double div = (a.x - b.x)*(c.y - d.y) - (a.y - b.y) * (c.x - d.x);
		if(div == 0.0){
			if(b == c and a <= c) return b;
			else if(a == d and a >= c) return a;
		}
		return point(x/div, y/div);
	}
	/* operators */
	bool operator == (const point& i) const { return x == i.x && y == i.y; }
	bool operator <  (const point& i) const { return x < i.x || x == i.x && y < i.y; }
	bool operator >  (const point& i) const { return i < *this; }
	bool operator != (const point& i) const { return !(*this == i); }
	bool operator <= (const point& i) const { return *this < i || *this == i; }
	bool operator >= (const point& i) const { return *this > i || *this == i; }
	friend int operator * (point a, point b) { return a.x * b.y - a.y * b.x; } // cross product
	friend point operator + (point a, point b) { return { a.x + b.x, a.y + b.y }; }
	friend point operator - (point a, point b) { return { a.x - b.x, a.y - b.y }; }
	friend istream& operator >> (istream& in, point& i) { in >> i.x >> i.y; return in; }
};

struct line {
	point a, b;
	/* constructors */
	line() {}
	line(point a, point b) : a(a), b(b) { if (a > b) swap(a, b); }
	/* methods */
	double length() { return sqrt(dist(a, b)); }
	bool is_on_line(point c) { return !ccw(a, b, c) && min(a, b) <= c && c <= max(a, b); }
	friend int is_cross(line a, line b) { return is_cross(a.a, a.b, b.a, b.b); }
	// point to line distance
	friend double dist(line a, point b) {
		auto CCW = [&](point& a, point& b, point& c) -> int {
		    return (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
		};
		return CCW(a.a, a.b, b) / a.length();
	}
	/* operators */
	friend istream& operator >> (istream& in, line& i) { in >> i.a >> i.b; return in; }
};

struct polygon {
	vector<point> v;
	/* constructors */
	polygon() {}
	polygon(vector<point> v) : v(v) {}
	/* methods */
	void convex_hull() { // convex hull in O(nlogn), ccw(v[i], v[i + 1], v[i + 2]) == 1
		if (v.size() < 3) return;
		swap(v[0], *min_element(v.begin(), v.end()));
		sort(v.begin() + 1, v.end(), [&](const point& a, const point& b) {
			int cw = ccw(v[0], a, b);
			if (cw) return cw > 0;
			return dist(v[0], a) < dist(v[0], b);
		});
		vector<point> res;
		for (const auto& i : v) {
			while (res.size() >= 2 && ccw(res[res.size() - 2], res.back(), i) <= 0) res.pop_back();
			res.push_back(i);
		}
		v = res;
	}
	double rotating_calipers() { // maximum distance in O(n), must be convex polygon
        if (v.size() < 2) return 0;
		int n = v.size();
		int l = 0, r = max_element(v.begin(), v.end()) - v.begin();
		double ret = sqrt(dist(v[l], v[r]));
		for (int i = 0; i < n; i++) {
			if ((v[(l + 1) % n] - v[l]) * (v[(r + 1) % n] - v[r]) < 0) l = (l + 1) % n;
			else r = (r + 1) % n;
			ret = max(ret, sqrtl(dist(v[l], v[r])));
		}
		return ret;
	}
	int point_in_polygon_naive(point a) { // O(qn), for all polygon, inside : 1, boundary : -1
		if (v.size() < 3) return 0;
		line cur(a, { int(1e9), a.y + 1 });
		int cnt = 0;
		for (int i = 0; i < v.size(); i++) {
			line l(v[i], v[(i + 1) % v.size()]);
			if (is_cross(cur, l) == -1) cnt++;
			if (l.is_on_line(a)) return -1;
		}
		return cnt % 2;
	}
	int point_in_polygon(point a) { // O(qlogn), for convex polygon only
		if (v.size() < 3) return 0;
		if (a < v[0] || ccw(v[0], v[1], a) < 0 || ccw(v[0], v.back(), a) > 0) return 0;
		if (ccw(v[0], v[1], a) == 0) return line(v[0], v[1]).is_on_line(a) ? -1 : 0;
		if (ccw(v[0], v.back(), a) == 0) return line(v[0], v.back()).is_on_line(a) ? -1 : 0;
		int lo = 0, hi = v.size();
		while (lo + 1 < hi) {
			int mid = lo + hi >> 1;
			if (ccw(v[0], v[mid], a) > 0) lo = mid;
			else hi = mid;
		}
		int cw = ccw(v[lo], v[lo + 1], a);
		return cw ? cw > 0 ? 1 : 0 : -1;
	}
	double area() {
		auto CCW = [&](point& a, point& b, point& c) -> int {
		    return (b.x - a.x) * (c.y - b.y) - (c.x - b.x) * (b.y - a.y);
		};
		int ret = 0;
		for (int i = 1; i < v.size() - 1; i++) {
			ret += CCW(v[0], v[i], v[i + 1]);
		}
		return abs(ret) / 2.;
	}
};

int32_t main() {
    fastio;
}
