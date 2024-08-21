// 배열 옮기기 K가 엄청 클 때 사용 가능
// using : https://atcoder.jp/contests/abc367/submissions/56927139
struct Replacement{
    int n;
    int* dat;

    Replacement(void) = default;
    Replacement(int _n) {
        n = _n;
        dat = new int[n + 1];
        for(int i = 1; i <= n; i++){
            dat[i] = i;
        }
    }
    ~Replacement(){
        delete[] dat;
    }

    int& operator [] (int i) const{
        return dat[i];
    }
    int& operator [] (int i){
        return dat[i];
    }

    Replacement& operator = (const Replacement& rhs){
        if(this == &rhs) return *this;

        n = rhs.n;
        delete[] dat;
        dat = new int[n + 1];
        for(int i = 1; i <= n; i++){
            dat[i] = rhs[i];
        }

        return *this;
    }

    friend Replacement operator * (const Replacement& lhs, const Replacement& rhs){
        if(lhs.n != rhs.n) throw "Error : replacement size not equal";

        Replacement res(lhs.n);
        for(int i = 1; i <= lhs.n; i++){
            res[i] = lhs[rhs[i]];
        }

        return res;
    }

    friend std::ostream& operator << (std::ostream& os, const Replacement& rhs){
        os << "[ ";
        for(int i = 1; i <= rhs.n; i++){
            os << rhs[i] << " ";
        }
        os << "]";

        return os;
    }

};

inline Replacement quickpow(Replacement& r, ll k){
    Replacement res(r.n);

    while(k){
        if(k & 1) res = res * r;
        r = r * r;
        k >>= 1;
    }
    return res;
}
