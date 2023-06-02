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
Max Flow AC Code
BOJ 10976
problem ref : https://www.acmicpc.net/problem/10976
Get Max Flow using FordFulkerson 
*/

constexpr int INF = 1e9 + 7;

class FordFulkerson{
	private:
		vector<vector<int>> flow,capacity,adjList;
		int s,e,n; // source, sink, verties
	public:
		FordFulkerson(){ n = 0,s = -1,e = -1;}
		FordFulkerson(int n){
			this->n = n;
			flow.resize(n + 1),capacity.resize(n + 1),adjList.resize(n + 1);
			for(int i = 0; i <= n; i++){
				flow[i].resize(n + 1);
				capacity[i].resize(n + 1);
			}
			s = -1,e = -1;
		}
		FordFulkerson(int n,int source,int sink){
			this->n = n;
			flow.resize(n + 1),capacity.resize(n + 1),adjList.resize(n + 1);
			for(int i = 0; i <= n; i++){
				flow[i].resize(n + 1);
				capacity[i].resize(n + 1);
			}
			s = source,e = sink;
		}
		void setSource(int t){s = t;}
		void setSink(int t) {e = t;}
		void AddEdge(int start,int end,int cap,bool directed = 1){
			adjList[start].push_back(end);
			adjList[end].push_back(start);
			capacity[start][end] += cap;
			if(!directed) capacity[end][start] += cap;
		}
		
		int MaxFlow(){
			if(s == -1 || e == -1) return -1;
			vector<int> par(n + 1);
			queue<int> q;
			int ret = 0;
			while(1){
				fill(par.begin(), par.end(), -1);
				q = queue<int>(); q.push(s);
				while(!q.empty()){
					int cur = q.front(); q.pop();
					for(auto nxt : adjList[cur]){
						if(par[nxt] == -1 && capacity[cur][nxt] - flow[cur][nxt] > 0){
							q.push(nxt); par[nxt] = cur;
							if(nxt == e) break;
						}
					}
				}
				if(par[e] == -1) break;
				int cost = INF;
				for(int i = e; i != s; i = par[i]){
					int a = par[i],b = i;
					cost = min(cost, capacity[a][b] - flow[a][b]);
				}
				ret += cost;
				for(int i = e; i != s; i = par[i]){
					int a = par[i],b = i;
					flow[a][b] += cost; flow[b][a] -= cost;
				}
			}
			return ret;
		}
};

int32_t main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int t; cin >> t;
    while(t--){
        int n,m; cin >> n >> m;
        FordFulkerson FF(n, 1, n);
        while(m--){
            int a,b; cin >> a >> b;
            FF.AddEdge(a, b, 1);
        }
        cout << FF.MaxFlow() << "\n";
    }
    return 0;
}
