#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/rope>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

#define int int_fast64_t

/*
Related Problems

https://www.acmicpc.net/problem/12583
https://www.acmicpc.net/problem/12584
https://www.acmicpc.net/problem/11559

참고 : https://ps.mjstudio.net/tip-array-control
*/

const int PRECISION = 0;

// 밑으로 중력
void Gravity(){
    for(int j = 0; j < n; j++) for(int i = n - 1; i >= 0; i--){
         int temp = i - 1;
         while(board[i][j] == '.' and temp >= 0) swap(board[i][j], board[temp--][j]);
     }
};

// 90도 시계방향으로 회전
vector<string> Rotate(){
    auto ret = ResetBoard();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) ret[i][j] = board[n - 1 - j][i];
    }
    return ret;
};


void Main(){
    
}

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed); cout.precision(PRECISION);
    Main();
    return 0;
}
