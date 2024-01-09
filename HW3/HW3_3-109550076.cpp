#include <bits/stdc++.h>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
#define MAXN 100000
using namespace std;

int parent[MAXN+1];
int depth[MAXN+1];
int visited[MAXN+1];


int dfs(const int x, vector<vector<int>> &edge) {
    visited[x] = 1;
    int leaf_depth = 0;
    for(const auto &i : edge[x]) {
        if(!visited[i]) {
            parent[i] = x;
            leaf_depth = max(leaf_depth, dfs(i, edge));
        }
    }
    depth[x] = leaf_depth;
    return leaf_depth + 1;
}

int solve() {
    int n;
    cin >> n;
    vector<vector<int>> edge(n+1);

    for(int i = 0;i < n-1;i++) {
        int p, q;
        cin >> p >> q;
        edge[p].emplace_back(q);
        edge[q].emplace_back(p);
    }


    visited[1] = 1;
    depth[1] = 0;
    parent[1] = -1;

    dfs(1, edge);

    for(int i = 1;i <= n;i++) {
        cout << depth[i] << ' ' << parent[i] << '\n';
    }
    return 0;
}


int main() {io
    solve();
    return 0;
}