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

/*
Bitset LCS 
BOJ 18439 AC Code
problem url : https://www.acmicpc.net/problem/18439
bitset ref code : https://github.com/ShahjalalShohag/code-library/blob/master/Strings/Bit%20LCS.cpp
*/

using ll = long long;

const int sz = 5e4 + 9, alphasz = 26;
const int W = 62;
int M;
struct BS{
	ll u[sz / W + 5];
	void clear(){
		memset(u, 0, sizeof u);
	}
	void set(int x){
		u[x / W] |= 1ll << (x % W);
	}
	BS operator | (const BS& r) const {
		BS s;
		for(int i = 0; i < M; i++){
			s.u[i] = u[i] | r.u[i];
		}
		return s;
	};
	void And(const BS& r){
		for(int i = 0; i < M; i++){
			u[i] = (u[i] ^ r.u[i]) & r.u[i];
		}
	}
	void sub(const BS& r){
		for(int i = 0; i < M; i++) u[i] = r.u[i] - u[i];
		for(int i = 0; i < M; i++) if(u[i] < 0){
			u[i] += 1ll << W;
			u[i + 1]--;
		}
	}
	void shl(){
		ll c = 1;
		for(long i = 0; i < M; i++){
			u[i] <<= 1;
			u[i] |= c;
			c = u[i] >> W & 1;
			u[i] ^= c << W;
		}
	}
	int count() const{
		int c = 0;
		for(int i = 0; i < M; i++){
			c += __builtin_popcountll(u[i]);
		}
		return c;
	}
};

BS ret, bs[alphasz], x;

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	for(int i = 0; i < alphasz; i++) bs[i].clear();
	string a,b; cin >> a >> b;
	if(a.size() > b.size()) swap(a, b);
	for(int i = 0; i < a.size(); i++){
		bs[a[i] - 'A'].set(i);
	}
	M = a.size() / W + (a.size() % W != 0);
	ret.clear();
	for(int i = 0; i < b.size(); i++){
		for(int j = 0; j < M; j++){
			x.u[j] = ret.u[j] | bs[b[i] - 'A'].u[j];
		}
		ret.shl();
		ret.sub(x);
		ret.And(x);
	}
	cout << ret.count() << "\n";
    return 0; 
}
