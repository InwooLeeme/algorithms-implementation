### 우선순위 큐를 이용한 스위핑법

보통 그리디에서 활용됨.

코드 1번
직접 수직선을 그려보면 이해가 됨
시작할 때 PQ에 저장된 값은 처음 선분의 끝점이고, 만약 top의 값보다 다음 선분의 시작점이 크거나 같다면 겹쳐있지 않다는 소리이니 pop
순회하면서 선분의 끝값들을 계속 푸쉬해줌
PQ의 사이즈가 곧 겹쳐있는 선분의 개수

```cpp
    int N; sf1(N);
    min_heap<int> PQ;
    vector<pii> v(N);
    for(auto& [a, b] : v) sf2(a, b);
    sort(all(v)); // 오름차순
    int mx = 0,ret = 0;
    PQ.push(v[0].second);
    for(int i = 1; i < N; i++){
        auto [st, en] = v[i];
        if(PQ.size() and PQ.top() <= st) PQ.pop(); // 1
        PQ.push(en);
        mx = max<int>(mx, PQ.size());
    }
    pf1l(mx);
```

#### Problem
https://www.acmicpc.net/problem/11000
