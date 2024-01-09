#include <bits/stdc++.h>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
using namespace std;
typedef long long lovelive;
typedef pair<lovelive, lovelive> pii;

void dijkstra(int x, vector<lovelive>* dist, vector<vector<pii>>* vec) {
    priority_queue<pii, vector<pii>, greater<>> pq;
    pq.emplace(0, x);
    (*dist)[x] = 0;
    while(!pq.empty()) {
        pii p = pq.top();
        pq.pop();
        lovelive u = p.second;
        for(auto& i : (*vec)[u]) {
            lovelive v = i.first;
            lovelive w = i.second;
            if((*dist)[v] > (*dist)[u] + w) {
                (*dist)[v] = (*dist)[u] + w;
                pq.emplace((*dist)[v], v);
            }
        }
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pii>> vec(n+2, vector<pii>());
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        vec[v].emplace_back(u, w);
    }

    vector<lovelive> dist_1(n+1, LLONG_MAX);
    vector<lovelive> dist_n(n+1, LLONG_MAX);
    dijkstra(1, &dist_1, &vec);
    dijkstra(n, &dist_n, &vec);

    if(k == 1) {
        for(int i = 1;i <= n;i++) {
            cout << (dist_1[i] < LLONG_MAX ? dist_1[i] : -1) << ' ';
        }
    } else {
        vector<vector<pii>> merged_vec(vec);
        for(int i = 1;i <= n;i++) {
            if(dist_1[i] < LLONG_MAX && dist_n[i] < LLONG_MAX) {
                merged_vec[n+1].emplace_back(i, dist_1[i] + dist_n[i]);
            }
        }
        vector<lovelive> dist(n+2, LLONG_MAX);
        dijkstra(n+1, &dist, &merged_vec);
        for(int i = 1;i <= n;i++) {
            cout << (dist[i] < LLONG_MAX ? dist[i] : -1) << ' ';
        }
    }
    cout << '\n';
}


int main() {io
    int n, m;
    cin >> n >> m;
    while(n--)
        solve();
    return 0;
}