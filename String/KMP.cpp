#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
#define int int64_t

vector<int> Fail(const string& s){
    const int n = s.size(); vector<int> f(n);
    for(int i = 1,j = 0; i < n; i++){
        while(j && s[i] != s[j]) j = f[j - 1];
        if(s[i] == s[j]) f[i] = ++j;
    }
    return f;
}

vector<int> KMP(const string& a,const string& b){
    const int n = a.size(), m = b.size();
    vector<int> ret, f = Fail(b);
    for (int i = 0, j = 0; i < n; i++) {
        while (j && a[i] != b[j]) j = f[j - 1];
        if (a[i] == b[j] && ++j == m) {
            ret.push_back(i - m + 1);
            j = f[j - 1];
        }
    }
    return ret;
}

int32_t main(){
    fastio;

}