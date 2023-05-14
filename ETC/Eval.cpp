/* Eval struct using c++
 BOJ 1918 AC Code
 Problem : https://www.acmicpc.net/problem/1918
*/ 
# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")
# pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t

template<typename T>
struct _Eval{
	string ops = "+-*/%()";
	bool is_op(char c) { return ops.find(c) != string::npos; }
	bool is_op(string c) { return c.size() == 1 && is_op(c[0]); }
	T run_op(T a, T b, char op) {
		if (op == '+') return a + b;
		else if (op == '-') return a - b;
		else if (op == '*') return a * b;
		else if (op == '/') return a / b;
		else return a % b;
	}
	T run_op(T a, T b, string op) { return run_op(a, b, op[0]); }
	int op_priority(string op) {
		if (op == "*" || op == "/" || op == "%") return 3;
		else if (op == "+" || op == "-") return 2;
		else return 1;
	}
	T calc_infix(const string &s) { return calc_postfix(to_postfix(s)); }
	T calc_postfix(const vector<string> &s) {
	   vector<T> ret;
	   for (auto &c: s) {
	      if (is_op(c)) {
	         T val = run_op(ret[ret.size() - 2], ret[ret.size() - 1], c[0]);
	         ret.pop_back(), ret.pop_back(), ret.push_back(val);
	      } else {
	         // Warning: long long conversion will cause crash on bigint usage
	         ret.push_back(stoll(c));
	      }
	   }
	   return ret[0];
	}
	vector<string> to_postfix(const vector<string> &s) {
	   vector<string> ret, op;
	   for (auto &c: s) {
	      if (is_op(c)) {
	         if (c == "(") op.push_back("(");
	         else if (c == ")") {
	            while (op.size() && op.back() != "(") ret.push_back(op.back()), op.pop_back();
	            op.pop_back();
	         } else {
	            while (op.size() && op_priority(op.back()) >= op_priority(c)) ret.push_back(op.back()), op.pop_back();
	            op.push_back(c);
	         }
	      } else {
	         ret.push_back(c);
	      }
	   }
	   while (op.size()) ret.push_back(op.back()), op.pop_back();
	   return ret;
	}
	vector<string> to_postfix(const string &s) { return to_postfix(parse(s)); }
	vector<string> parse(const string &s) {
		vector<string> ret;
		string tmp;
		const int sz = s.size();
		for (int i = 0; i < sz; i++) {
			if (is_op(s[i])) ret.push_back(string(1, s[i]));
			else if (i == s.size() - 1 || is_op(s[i + 1])) ret.push_back(tmp + s[i]), tmp = "";
			else tmp += s[i];
		}
	   if (ret.size() && ret[0] == "-") { // leading negative operator
			ret[1] = "-" + ret[1];
			ret.erase(ret.begin());
		}
		return ret;
	}
	string to_raw(const vector<string> &s) {
		string ret;
		for (auto & c: s) ret += c;
		return ret;
	}
};

_Eval<int> EV;

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s; cin >> s;
	for(const auto& c : EV.to_postfix(s)) cout << c;	
    return 0;   
}
