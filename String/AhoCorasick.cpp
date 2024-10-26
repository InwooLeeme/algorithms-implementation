// ref : https://github.com/kth-competitive-programming/kactl/blob/main/content/strings/AhoCorasick.h

// 사용할 때 알파벳 숫자에 맞게 알파벳과 첫 문자의 값 수정해주기
// find(x) is $O(N)$, where N = length of x. findAll is $O(NM)$.
struct AhoCorasick {
	enum {alpha = 26, first = 'A'}; // change this!
	struct Node {
		// (nmatches is optional)
		int back, next[alpha], start = -1, end = -1, nmatches = 0;
		Node(int v) { memset(next, v, sizeof(next)); }
	};
	vector<Node> N;
	vector<int> backp;
	void insert(string& s, int j) {
		assert(!s.empty());
		int n = 0;
		for (char c : s) {
			int& m = N[n].next[Cv(c)];
			if (m == -1) { n = m = N.size(); N.emplace_back(-1); }
			else n = m;
		}
		if (N[n].end == -1) N[n].start = j;
		backp.push_back(N[n].end);
		N[n].end = j;
		N[n].nmatches++;
	}
	AhoCorasick(vector<string>& pat) : N(1, -1) {
        for(int i = 0; i < pat.size(); i++) insert(pat[i], i);
		N[0].back = N.size();
		N.emplace_back(0);

		queue<int> q;
		for (q.push(0); !q.empty(); q.pop()) {
			int n = q.front(), prev = N[n].back;
            for(int i = 0; i < alpha; i++){
				int &ed = N[n].next[i], y = N[prev].next[i];
				if (ed == -1) ed = y;
				else {
					N[ed].back = y;
					(N[ed].end == -1 ? N[ed].end : backp[N[ed].start])
						= N[y].end;
					N[ed].nmatches += N[y].nmatches;
					q.push(ed);
				}
			}
		}
	}
	vector<int> find(string word) {
		int n = 0;
		vector<int> res; // ll count = 0;
		for (char c : word) {
			n = N[n].next[Cv(c)];
			res.push_back(N[n].end);
			// count += N[n].nmatches;
		}
		return res;
	}
	vector<vector<int>> findAll(vector<string>& pat, string word) {
		vector<int> r = find(word);
		vector<vector<int>> res(word.size());
        for(int i = 0; i < word.size(); i++){
			int ind = r[i];
			while (ind != -1) {
				res[i - pat[ind].size() + 1].push_back(ind);
				ind = backp[ind];
			}
		}
		return res;
	}
};
