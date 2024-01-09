#include <bits/stdc++.h>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
using namespace std;
typedef long long ll;

// disjoint set
struct disjoint_set {
    vector<int> parent, rank;
    int trees;

    explicit disjoint_set(const int n) : parent(n+1), rank(n+1, 0), trees(n) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        if(parent[x] == x)
            return x;

        int root = find(parent[x]);
        return parent[x] = root;
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y)
            return;
        if(rank[x] > rank[y])
            swap(x, y);
        parent[x] = y;
        rank[y] += rank[x];
        trees--;
    }
};

ll solve() {
    int n, m;
    cin >> n >> m;

    vector<ll> weights(n+1);
    int min_idx = -1;
    for(int i = 1;i <= n;i++) {
        cin >> weights[i];
        if(min_idx == -1 || weights[i] < weights[min_idx])
            min_idx = i;
    }

    priority_queue<tuple<ll, ll, ll>, vector<tuple<ll, ll, ll>>, greater<>> offers;
    for(int i = 0;i < m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if(w < weights[u] + weights[v])
            offers.emplace(w, u, v);
    }

    for(int i = 1;i <= n;i++)
        if(i != min_idx)
            offers.emplace(weights[min_idx] + weights[i], min_idx, i);

    ll ans = 0;
    disjoint_set ds(n);

    while(!offers.empty()) {
        auto [w, u, v] = offers.top();
        offers.pop();
        if(ds.find(u) != ds.find(v)) {
            ds.unite(u, v);
            ans += w;
        }
    }

    return ans;
}


int main() {io
    int n;
    cin >> n;
    while(n--)
        cout << solve() << endl;
    return 0;
}