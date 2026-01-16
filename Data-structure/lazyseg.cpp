// 0 index
template <class Traits>
struct LazySegTree {
    using S = typename Traits::S;
    using F = typename Traits::F;

    int n;                 // original size
    vector<S> seg;         // 4n
    vector<F> lz;          // 4n

    LazySegTree() : n(0) {}

    explicit LazySegTree(int N) { init(N); }

    explicit LazySegTree(const vector<S>& a) { init((int)a.size()); build(a); }

    void init(int N) {
        n = N;
        seg.assign(4 * n + 5, Traits::e());
        lz.assign(4 * n + 5, Traits::id());
    }

    void build(const vector<S>& a) {
        init((int)a.size());
        build(1, 0, n - 1, a);
    }

    // range apply [l, r]
    void apply(int l, int r, const F& f) {
        apply(1, 0, n - 1, l, r, f);
    }

    // range query [l, r]
    S prod(int l, int r) {
        return prod(1, 0, n - 1, l, r);
    }

    // point get/set (optional convenience)
    S get(int i) { return prod(i, i); }

    void set_point(int i, const S& x) { set_point(1, 0, n - 1, i, x); }

private:
    void build(int idx, int l, int r, const vector<S>& a) {
        if (l == r) { seg[idx] = a[l]; return; }
        int mid = (l + r) >> 1;
        build(idx << 1, l, mid, a);
        build(idx << 1 | 1, mid + 1, r, a);
        seg[idx] = Traits::op(seg[idx << 1], seg[idx << 1 | 1]);
    }

    // apply f to node idx representing segment [l, r]
    inline void all_apply(int idx, int l, int r, const F& f) {
        seg[idx] = Traits::mapping(f, seg[idx], r - l + 1);
        lz[idx]  = Traits::composition(f, lz[idx]); // old 먼저, new 나중
    }

    inline void push(int idx, int l, int r) {
        if (l == r) return;
        if (Traits::is_id(lz[idx])) return;
        int mid = (l + r) >> 1;
        all_apply(idx << 1,     l,     mid, lz[idx]);
        all_apply(idx << 1 | 1, mid+1, r,   lz[idx]);
        lz[idx] = Traits::id();
    }

    void apply(int idx, int l, int r, int ql, int qr, const F& f) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            all_apply(idx, l, r, f);
            return;
        }
        push(idx, l, r);
        int mid = (l + r) >> 1;
        apply(idx << 1, l, mid, ql, qr, f);
        apply(idx << 1 | 1, mid + 1, r, ql, qr, f);
        seg[idx] = Traits::op(seg[idx << 1], seg[idx << 1 | 1]);
    }

    S prod(int idx, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return Traits::e();
        if (ql <= l && r <= qr) return seg[idx];
        push(idx, l, r);
        int mid = (l + r) >> 1;
        return Traits::op(
            prod(idx << 1, l, mid, ql, qr),
            prod(idx << 1 | 1, mid + 1, r, ql, qr)
        );
    }

    void set_point(int idx, int l, int r, int pos, const S& x) {
        if (l == r) {
            seg[idx] = x;
            lz[idx]  = Traits::id();
            return;
        }
        push(idx, l, r);
        int mid = (l + r) >> 1;
        if (pos <= mid) set_point(idx << 1, l, mid, pos, x);
        else set_point(idx << 1 | 1, mid + 1, r, pos, x);
        seg[idx] = Traits::op(seg[idx << 1], seg[idx << 1 | 1]);
    }
};

struct RangeAddRangeSum {
    using S = long long;  // sum
    using F = long long;  // add

    static S e() { return 0LL; }
    static F id() { return 0LL; }

    static S op(S a, S b) { return a + b; }

    static S mapping(F f, S x, int len) {
        return x + f * 1LL * len;
    }

    // composition(f_new, f_old): old 먼저, new 나중
    static F composition(F f_new, F f_old) {
        return f_old + f_new;
    }

    static bool is_id(F f) { return f == 0LL; }
};
// rules
/* 
1) S와 op, e 규칙 (모노이드)
 op : S × S → S

구간 왼쪽/오른쪽 정보를 합쳐 “부모 구간 정보”를 만드는 연산.

필수 조건

결합법칙(Associativity)
op(op(a,b),c) == op(a, op(b,c))

세그트리는 어떤 식으로 묶어서 합쳐도 같은 결과여야 함.

항등원(Identity) e() 존재
op(e(), x) == x 그리고 op(x, e()) == x

쿼리에서 “겹치지 않는 구간”을 반환할 때 쓰는 값이 e()임.

직관

sum이면 e=0

min이면 e=+INF

max이면 e=-INF

(구조체면) “merge 했을 때 아무 영향 없는 값”을 필드별로 만들기

2) F와 id 규칙 (lazy 연산의 항등)
 F는 “구간에 적용되는 업데이트 연산” 타입

예: add, assign, affine( ax+b ) 등

 id()는 “아무 것도 안 하는 연산”

필수 조건

모든 S x와 구간 길이 len에 대해
mapping(id(), x, len) == x

즉, id()를 적용하면 구간 정보가 그대로여야 해.

직관

add면 id=0

assign(=x)면 id = (hasSet=false) 같은 “비활성 상태”

affine( ax+b )면 id = (a=1, b=0)

3) mapping 규칙 (F가 S에 작용)
mapping : F × S × len → S

“연산 f를 이 구간(길이 len)의 요약값 x에 적용했을 때 요약값이 어떻게 바뀌는가”

필수 조건 A (항등)

mapping(id(), x, len) == x

필수 조건 B (합성과의 호환)

모든 f, g, x, len에 대해
mapping(composition(f, g), x, len) == mapping(f, mapping(g, x, len), len)

이게 진짜 핵심이야.
즉, lazy를 합쳐놓고 한 번에 적용한 결과와
g 먼저 적용하고 그다음 f 적용한 결과가 같아야 해.

이 조건이 깨지면 push/누적에서 값이 틀어짐.

len이 왜 필요?

sum 같은 건 “전체에 +v”면 +v*len이라 길이가 필수.

min/max는 길이가 필요 없을 수도 있지만, 일반화를 위해 항상 받는 게 안전.

4) composition 규칙 (lazy끼리 합치기)
 composition : F(new) × F(old) → F

의미는 보통 이렇게 고정해:

composition(f_new, f_old) = “old를 먼저 적용하고, new를 나중에 적용”한 것과 같은 하나의 lazy

그래서 계약은:

필수 조건 A (결합법칙)

composition(a, composition(b, c)) == composition(composition(a, b), c)
(표현 순서만 바뀌어도 같은 누적 결과)

필수 조건 B (항등원 id)

composition(id(), f) == f

composition(f, id()) == f

그리고 mapping 호환 조건(위 3-B)을 만족해야 함

직관 예시

구간 add: composition(new, old) = old + new

구간 assign: “나중 assign이 이전을 덮음”

new가 set이면 결과는 무조건 new

new가 no-op이면 결과는 old

assign + add 같이 섞이면 우선순위를 정해야 함

보통 set이 add를 “리셋”하거나, set 후 add는 setVal에 누적

5) “한 줄 체크리스트” (가장 실용적인 검증법)

네가 정의한 e/id/mapping/composition이 맞는지 빠르게 검산하는 방법:

op(e, x) == x 인가?

mapping(id, x, len) == x 인가?

랜덤 f,g,x,len 잡고
mapping(composition(f,g), x, len)
== mapping(f, mapping(g,x,len), len)
가 성립하는가?

composition(f, id) == f 인가?

이 4개만 맞으면 대개 구현이 안전.

6) 예시로 감 잡기: Range Add / Range Sum

S = sum

op = +, e=0

F = add, id=0

mapping(add, sum, len) = sum + add*len

composition(new, old) = old + new

여기서 3-B를 실제로 보면:

좌변: composition(f,g)=g+f → sum + (g+f)*len

우변: mapping(g) 후 mapping(f) → sum + g*len + f*len
같음 
*/
