#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

/* 
 알파벳 대문자로만 이루어진 문자열을 저장하는 트라이 구조체

*/

struct TrieNode{
	bool end;
	int child[26];
	TrieNode(){
		end = false;
		fill(child, child + 26, -1);
	}
};

struct Trie{
	vector<TrieNode> trie;
	int newNode(){
		TrieNode temp;
		trie.push_back(temp);
		return trie.size() - 1;
	}
	void add(string& s,int node = 0,int idx = 0){
		if(idx == s.size()){
			trie[node].end = true;
			return;
		}
		int c = s[idx] - 'A';
		if(trie[node].child[c] == -1){
			int nxt = newNode();
			trie[node].child[c] = nxt;
		}
		add(s, trie[node].child[c], idx + 1);
	}
	bool exist(string& s){
		int now = 0;
		for(int i = 0; i < s.size(); i++){
			int c = s[i] - 'A';
			if(trie[now].child[c] == -1) return false;
			now = trie[now].child[c];
		}
		return trie[now].end;
	}
	Trie(){
		newNode();
	}
};

int32_t main(){
    Trie T;
    string s = "ASDF";
    T.add(s);
    T.exist(s); // 
}