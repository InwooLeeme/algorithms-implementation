### Monotone Stack

스택 내부 원소들을 단조 증가 or 감소시키는 테크닉 O(N)이다.

https://justicehui.github.io/usaco/2019/04/11/BOJ6198/

```cpp
stack<int> S;
int ret = 0;
for(int i = 0; i < n; i++) cin >> v[i];
for(int i = 0; i < n; i++){
  while(S.size() and S.top() < v[i]) S.pop();
  ret += (int)S.size();
  S.push(v[i]);
}
```
