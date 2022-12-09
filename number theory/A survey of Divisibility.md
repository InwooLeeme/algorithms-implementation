# A survey of Divisibility ( 나눗셈 탐구 )

### 나눗셈 소개

#### 정의 1. 나눗셈

```
정수 a (a != 0)이 정수 b를 나눈다는 것은 a * m = b를 만족하는 정수 m이 있다는 뜻.
정수 b가 정수 a에 나누어 떨어지면 a | b라 나타낸다.
a는 b의 약수(divisor) 또는 인수(factor)라고 한다. b는 a의 배수(multiple)이라고 함.
```

###### 정리 1 : 약수의 성질

> 정수 a,b,c,d에 대하여 다음이 성립한다.
>
> 1. a | 1 <=> a = ±1
> 2. a | b, b | c 이면 a | c 이다.
> 3. a | b, c | d이면, (a _ c) | (b _ d)이다.
> 4. a | b, b | a <=> a = ±b
> 5. a | b이고 b가 0이 아니라면 abs(a) <= abs(b)

pf) 정리

1. pf)
   <=) a = ±1 이라면 1 | 1, -1 | 1
   =>) a | 1 이라면 a\*m = 1을 만족하는 정수 m이 존재, a = 1 / m을 의미하므로 m = ±1 즉, a = ±1

2. pf)
   a | b, b | c이므로 a*x = b를 만족하는 정수 x, b*y = c를 만족하는 정수 y가 존재
   axy = c이므로 곱셈의 결합 법칙에 의해 a(xy) = c가 성립
   xy는 정수들의 곱이므로 정수로 나타낼 수 있으니 a \* (정수) = c가 성립
   따라서 a | c

3. pf) a | b, c | d이면 (a _ c) | (b _ d)
   a | b이므로 am = b를 만족하는 정수 m, c | d이므로 cn = d를 만족하는 정수 n이 각각 존재.
   두 식을 곱하면 am _ cn = b _ d가 되고 직관적으로 ac * mn = b*d, mn은 정수들의 곱이니 정수이므로 ac*(정수) = bd가 되서 (a * c) | (b \* d)

4. pf) a | b, b | a <=> a = ±b
   <=>이니 <=부터 증명
   a = ±b 이면 a | b이고, b | a

   a | b, b | a이면 정수 x,y가 존재해서 다음 식이 성립
   ax = b,by = a 이는 axy = a이므로 xy = 1
   다음 식을 풀면 x = 1,y = 1 or x = -1,y = -1

5. pf) pass

##### τ(n) : 타우 함수(tau function)[!중요]

τ(n) : n의 양의 약수의 개수
τ(42) = 8 ( 1, 2, 3, 6, 7, 14, 21, 42)

```cpp
// time : O(Nsqrt(N)) 1 - indexed base
const int sz = 100'000;
vector<int> TauFunction(){
    vector<int> tau(sz + 1, 0);
    for(int i = 1; i <= sz; i++){
        for(int j = i; j <= sz; j += i){
            tau[j]++;
        }
    }
    return tau;
}
```

#### 최대 공약수(gcd)
```
양의 정수 g가 0이 아닌 두 정수 a,b의 최대 공약수 <=> 
1) g | a, g | b (g는 공약수), 2) 임의의 c에 대해 c | a, c | b이면, c <= g (c는 공약수)
```

##### 서로소
```
두 정수 a,b가 존재할 때 a,b의 gcd가 1이라면 두 수는 서로소(relatively prime)
```

다음엔 유명한 사실을 다룬다.
gcd(a, b) = g라면 gcd(a / g, b / g) = 1이 성립

##### 2개 이상의 정수에 대한 최대공약수
```
양의 정수가 g가 모든 원소가 0이 아닌 정수 집합 S = {a1,a2...an}의 최대공약수(gcd)이다
<=>
g는 집합 S의 모든 정수를 나누는 가장 큰 정수
```

##### 3개 이상의 최대공약수
```
세 정수 a,b,c가 존재할 때 최대공약수 g = gcd(a, gcd(b,c))
```

#### 요약
> 정수 a가 b의 약수라는 말은 a * m = b를 만족하는 정수 m이 존재한다는 것과 동치
> a | b, b | c 이면 a | c이고 a는 b와c의 임의의 일차결합을 나타냄
> a와 b의 gcd는 a,b를 나누는 가장 큰 공약수 
