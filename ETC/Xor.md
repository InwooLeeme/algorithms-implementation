### Xor Relate Problem

1. Xor는 4씩 주기성을 가진다.
2. x % 4 == 0 ? 0
3. x % 4 == 1 ? 1
4. x % 4 == 2 ? x + 1
5. x % 4 == 3 ? 0

참고 : https://www.geeksforgeeks.org/calculate-xor-1-n/

```cpp
int GetXor(int x){
    if(x % 4 == 0) return x;
    else if(x % 4 == 1) return 1;
    else if(x % 4 == 2) return x + 1;
    return 0;
}
```

#### [A,B]에 대하여 모두 Xor한 값 구하기
```cpp
// O(1)
int GetXor(int x){
    if(x % 4 == 0) return x;
    else if(x % 4 == 1) return 1;
    else if(x % 4 == 2) return x + 1;
    return 0;
}

// In [a,b]
int F(int a,int b){
  return GetXor(b) ^ GetXor(a - 1)
} 
```
