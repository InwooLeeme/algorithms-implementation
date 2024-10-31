// problem url : https://www.acmicpc.net/problem/2995
// 이 문제를 LDS커버임 원소가 엄격하게 증가하지 않아도 됨 -> 같거나 작은(upper_bound), 엄격하게 증가 or 감소해야한다면(lower_bound)
// LDS를 구할때는 -v[i].se로(음수로), LIS는 양수로

using pii = pair<int, int>;
int n; 

void Main(){
    ri(n);
    vector<pii> v(n); for(auto& [a, b] : v) ri(a, b);
    sort(all(v), [&](pii& a, pii& b){
        return a.fi == b.fi ? a.se > b.se : a.fi < b.fi;
    });
    v.erase(unique(all(v)), v.end());
    vector<int> LIS,path(n + 1);
    for(int i = 0; i < n; i++){
        auto t = -v[i].se;
        if(LIS.empty() or LIS.back() <= t){
            LIS.pb(t);
            path[i] = LIS.size();
        }
        else{
            auto idx = upper_bound(all(LIS), t) - LIS.begin();
            path[i] = idx + 1;
            *upper_bound(all(LIS), t) = t;
        }
    }
    vector<pii> ret;
    for(int i = n,t = LIS.size(); i >= 0; i--){
        if(path[i] != t) continue;
        ret.pb(v[i]),t--;
    }
    po(LIS.size());
    while(!ret.empty()){
        auto [a, b] = ret.back(); ret.pop_back();
        po(a, b);
    }
}   

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cout.setf(ios::fixed); cout.precision(PRECISION);
    Main();
    return 0;
}
