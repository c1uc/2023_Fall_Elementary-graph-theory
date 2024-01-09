#include <bits/stdc++.h>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
using namespace std;

struct edge {
    int u, v, capacity, flow;
    edge(int u, int v, int capacity, int flow) : u(u), v(v), capacity(capacity), flow(flow) {}
};

class Dinic {
private:
    vector<edge> edges;
    vector<vector<int>> adj;
    int n, m = 0, s, t;
    vector<int> level, ptr;
    queue<int> q;

public:
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int u, int v, int capacity) {
        edges.emplace_back(u, v, capacity, 0);
        edges.emplace_back(v, u, 0, 0);
        adj[u].push_back(m);
        adj[v].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : adj[u]) {
                if (edges[id].capacity - edges[id].flow < 1)
                    continue;
                if (level[edges[id].v] != -1)
                    continue;
                level[edges[id].v] = level[u] + 1;
                q.push(edges[id].v);
            }
        }
        return level[t] != -1;
    }

    int dfs(int u, int pushed) {
        if (pushed == 0)
            return 0;
        if (u == t)
            return pushed;
        for (int& cid = ptr[u]; cid < static_cast<int>(adj[u].size()); cid++) {
            int id = adj[u][cid];
            int v = edges[id].v;
            if (level[u] + 1 != level[v] || edges[id].capacity - edges[id].flow < 1)
                continue;
            int tr = dfs(v, min(pushed, edges[id].capacity - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    int flow() {
        int f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, INT_MAX)) {
                f += pushed;
            }
        }
        return f;
    }
};

int main() {io
    int n, m, s, t, k;
    cin >> n >> m >> k;

    s = 0, t = n + m + 1;
    int s_ = n + m + 2;

    Dinic dinic(n + m + 3, s, t);
    dinic.add_edge(s, s_, n + k);

    for(int i = 1;i <= n;i++) {
        dinic.add_edge(s_, i, 2);
        int c, q;
        cin >> c;
        for(int j = 0;j < c;j++) {
            cin >> q;
            dinic.add_edge(i, n + q, 1);
        }
    }

    for(int i = 1;i <= m;i++) {
        dinic.add_edge(n + i, t, 1);
    }

    cout << dinic.flow() << endl;
    return 0;
}
