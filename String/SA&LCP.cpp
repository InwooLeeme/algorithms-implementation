#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t

/*
9248 Suffix Array AC Code
https://www.acmicpc.net/problem/9248

Ref : 
https://gumgood.github.io/suffix-array-and-lcp
https://blog.naver.com/PostView.naver?blogId=kks227&logNo=221028710658&categoryNo=299&parentCategoryNo=0&viewDate=&currentPage=4&postListTopCurrentPage=1&from=postList&userTopListOpen=true&userTopListCount=5&userTopListManageOpen=false&userTopListCurrentPage=4
*/

// Build Suffix Array O(NlogN^2)
// result : 0 indexed base, 사전 순으로 i번째가 몇번째 접미사인지?
vector<int> GetSA(const string& s){
    const int n = s.size();
    vector<int> sa(n), r(n + 1), nr(n + 1);
    for(int i = 0; i < n; i++) sa[i] = i, r[i] = s[i];
    for(int d = 1; d < n; d <<= 1){
        auto Cmp = [&](int i, int j){ 
            return r[i] < r[j] || (r[i] == r[j] && r[i + d] < r[j + d]); // shifting 2^d
        };
        sort(sa.begin(), sa.end(), Cmp); // O(NlogN)
        nr[sa[0]] = 1;
        for(int i = 1; i < n; i++){
            nr[sa[i]] = nr[sa[i - 1]] + Cmp(sa[i - 1], sa[i]);
        }
        r = nr;
    }
    return sa;
}

// Get Longest Common Prefix using SA
// isa : sa의 반대, i번째 접미사가 사전 순으로 몇 번째인지?
// isa[sa[i]] = i 성립, isa[sa[i] - 1] : 사전 순으로 바로 앞에 있는 접미사
// Result : LCP 배열(SA배열의 i번째 접미사와 i - 1번째 접미사의 가장 긴 공통 접미사)
vector<int> LCP(vector<int>& sa, const string& s){
    const int n = s.size();
    vector<int> lcp(n), isa(n);
    for(int i = 0; i < n; i++) isa[sa[i]] = i;
    for(int k = 0, i = 0; i < n; i++) if(isa[i]){
        for(int j = sa[isa[i] - 1]; s[i + k] == s[j + k]; k++);
        lcp[isa[i]] = (k ? k-- : 0);
    }
    return lcp;
}

int32_t main(){
    fastio;
    string s; cin >> s;
    auto sa = GetSA(s);
    for(auto& i : sa) cout << i + 1 << " ";
    cout << "\n";
    auto lcp = LCP(sa, s);
    cout << "x ";
    for(int i = 1; i < lcp.size(); i++) cout << lcp[i] << ' ';
    return 0;
}
