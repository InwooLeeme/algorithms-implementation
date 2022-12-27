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

struct PalindromicTree{
  struct Node{
    int len;
    int sufflink;
    map<char, int> nxt;
  };
  string o;
  int cnt = 2;
  int lastsuff = 2;
  Node tree[200010];
  
  void Init(){
    tree[1] = {-1, 1, map<char,int>()};
    tree[2] = {0, 1, map<char,int>()};
    cin >> o;
    for(int i = 0; i < o.size(); i++){
      MakeNode(o[i], i);
    }
  }
  
  void MakeNode(char c,int pos){
    int cur = lastsuff;
    while(1){
      // 만약 palindrome을 만들 수 있다면
      if(pos - tree[cur].len - 1 >= 0 && c == o[pos - tree[cur].len - 1]) break; 
      cur = tree[cur].sufflink; // 그렇지 못한 경우 sufflink를 타고 간다.
    }
    if(tree[cur].nxt.count(c)){ // 만약 link에 해당하는 char가 존재한다면
      lastsuff = tree[cur].nxt[c]; // last를 바꿈.
      return;
    }
    int nxt = lastsuff = tree[cur].nxt[c] = ++cnt; // 새로운 노드 만듬
    tree[nxt].len = tree[cur].len + 2; // 길이 구함
    
    if(tree[nxt].len == 1){ // 만약 길이가 1이라면
      tree[nxt].sufflink = 2; // 2번 노드에 연결
      return;
    }
    
    while(cur > 1){
      cur = tree[cur].sufflink;
      // 만약 팰린드롬을 만들 수 있으면
      if(pos - tree[cur].len - 1 >= 0 && c == o[pos - tree[cur].len - 1){ 
        tree[nxt].sufflink = tree[cur].nxt[c]; // 해당 팰린드롬에 해당하는 노드에 연결
        break;
      }
    }
  }
};

int32_t main(){
  fastio;
  
  return 0;
}
