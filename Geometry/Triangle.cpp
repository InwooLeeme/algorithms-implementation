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
BOJ 7694 AC Code using Pick's theorem
ref : https://ilyoan.tistory.com/entry/Triangle
*/

template<typename T>
struct Triangle{
    using pt = pair<T, T>;
    pt A,B,C;
    Triangle(pt _A,pt _B, pt _C):A(_A),B(_B),C(_C){}
    void Input(){  }
    T Area(){ // gauss
        return abs((A.first * B.second + B.first*C.second + C.first * A.second) - (B.first*A.second + C.first*B.second + A.first*C.second)) / 2.0;
    }
    int BoundaryPoint(pt& a, pt& b){
        T dx = abs(a.first - b.first);
        T dy = abs(a.second - b.second);
        int g = __gcd(max<T>(dx, dy), min<T>(dx, dy));
        return g - 1;
    }
    int CountBoundaryPoint(){
        return BoundaryPoint(A, B) + BoundaryPoint(B, C) + BoundaryPoint(C, A);
    }
    int Pick(){
        auto area = Area();
        auto bp = CountBoundaryPoint() + 3;
        int ip = area - bp / 2 + 1;
        return ip;
    }
};

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    pair<int, int> A, B, C;
    while(cin >> A.first >> A.second >> B.first >> B.second >> C.first >> C.second){
        if(A.first == 0 and A.second == 0 and B.first == 0 and B.second == 0 and C.first == 0 and C.second == 0) break;
        Triangle<int> TR(A,B,C);
        cout << TR.Pick() << "\n";
    }
    return 0;
}
