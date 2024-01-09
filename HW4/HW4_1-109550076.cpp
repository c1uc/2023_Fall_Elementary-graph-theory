#include<bits/stdc++.h>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
using namespace std;

vector<vector<int>> vec;

vector<bool> vis;
vector<int> tin, low;
set<int> cutpoints;
int t = 0;

void DFS(int u, int p = -1) {
    int children = 0;
    vis[u] = true;
    tin[u] = low[u] = ++t;
    for (int v : vec[u]) {
        if (v == p) continue;
        if (!vis[v]) {
            children++;
            DFS(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] >= tin[u] && p != -1)
                cutpoints.insert(u);
        }
        else if (v != p)
            low[u] = min(low[u], tin[v]);
    }
    if (p == -1 && children > 1)
        cutpoints.insert(u);
}

int main() {io
    int nodes, edges, u, v;
    cin >> nodes >> edges;
    vec.resize(nodes+1, vector<int>());

    for (int i = 0; i < edges; i++) {
        cin >> u >> v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }

    vis.assign(nodes+1, false);
    tin.assign(nodes+1, 0x3f3f3f3f);
    low.assign(nodes+1, 0x3f3f3f3f);
    for (int i = 1; i <= nodes; i++)
        if (!vis[i])
            DFS(i);

    cout << cutpoints.size() << endl;
    for (int u : cutpoints)
        cout << u << " ";
    return 0;
}