// 1 based
template<typename T>
struct Fenwick1D{
    int sz;
    vector<T> tree,data;
    int lowbit(int x) const{ return x & (-x); }
    Fenwick1D(int n):sz(n),tree(sz + 1),data(sz + 1){}
    void Update(int i, T val){ // v[x] += val
        while(i <= sz){
            tree[i] += val;
            i += lowbit(i);
        }
    }
    void Set_Val(int i, T val){ // v[x] = val
        int delta = val - data[i];
        data[i] = val;
        Update(i, delta);
    }
    T Query(int idx) const{
        int ret = 0;
        int i = idx;
        while(i > 0){
            ret += tree[i];
            i -= lowbit(i);
        }
        return ret;
    }
    T Query_Range(int l, int r) const{
        return Query(r) - Query(l - 1);
    }
    T Get_Val(int i) const{ // return v[x]
        return data[i];
    }
};
