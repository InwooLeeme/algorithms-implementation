const int PRECISION = 0;

const int INF = int(1e18);

// Problem URL : https://www.acmicpc.net/problem/9345
// ref : https://www.acmicpc.net/source/57600099
// 노드 구조체, + operator만 설정해서 넘겨주기

struct Node{
	int mx, mn;
	Node():mx(-INF),mn(INF){}
	Node(int x):mx(x),mn(x){}
};

Node operator+(Node a, Node b){
	Node res;
	res.mx = max<int>(a.mx, b.mx);
	res.mn = min<int>(a.mn, b.mn);
	return res;
}

template<typename T>
struct SegTree{
	int sz;
	vector<T> tree;
	SegTree(int _sz):sz(1 << _sz), tree(1 << _sz + 1, T()){}

	void Update(int i, T val){
		--i |= sz, tree[i] = val;
		while(i >>= 1) tree[i] = tree[i << 1] + tree[i << 1 | 1];
	}

	T Query(int l, int r){
		T ret = T(); --l |= sz, --r |= sz;
		while(l <= r){
			if(l & 1) ret = ret + tree[l++];
			if(~r & 1) ret = ret + tree[r--];
			l >>= 1, r >>= 1;
		}
		return ret;
	}
};

void Main(){
	int t; ri(t); while(t--){
		int n,m; ri(n, m);
		vi v(n + 1); iota(v.begin(), v.end(), 0);
		SegTree<Node> ST(17);
		for(int i = 1; i <= n; i++) ST.Update(i, Node(i));
		while(m--){
			int t,a,b; ri(t, a, b); ++a,++b;
			if(!t){
				swap(v[a], v[b]);
				ST.Update(a, Node(v[a])); ST.Update(b, Node(v[b]));
			}
			else{
				auto [mx, mn] = ST.Query(a, b);
				if(mn == a and mx == b) po("YES");
				else po("NO");
			}
		}
	}
}

int32_t main(){
	ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed); cout.precision(PRECISION);
	Main();
	return 0;
}
