// Lucas(n) mod MOD 
/* 
쓰임새 예
원형 그래프 𝐶𝑛 의 매칭 개수 = 𝐿𝑛​
(경로𝑃𝑛의 매칭 개수는 𝐹𝑛+2Fn+2).
예: 원탁에서 각 사람이 이웃과만 악수하는 경우의 수 = 𝐿𝑛
원형 타일링, 라더 그래프 변형 등에서도 등장.
*/
#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

pair<int64,int64> fib(long long n, int64 MOD){
    if(n==0) return {0,1};
    auto [a,b] = fib(n>>1, MOD); // a=F(k), b=F(k+1)
    int64 two_b_minus_a = (2*b - a) % MOD; if(two_b_minus_a<0) two_b_minus_a += MOD;
    int64 c = (a * two_b_minus_a) % MOD;         // F(2k)
    int64 d = ( (a*a % MOD) + (b*b % MOD) ) % MOD; // F(2k+1)
    if((n&1)==0) return {c,d};
    return {d, (c + d) % MOD};
}
int main(){
    long long n; long long MOD = 1000000007; 
    cin >> n;
    auto [Fn, Fnp1] = fib(n, MOD);
    // L_n = 2*F_{n+1} - F_n (mod MOD)
    long long Ln = ( (2*Fnp1 % MOD) - Fn ) % MOD;
    if(Ln<0) Ln += MOD;
    cout << Ln << "\n";
}
