#include <bits/stdc++.h>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
using namespace std;

typedef pair<int, int> pii;

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

    void reset(int s, int t) {
        m = 0;
        this->s = s;
        this->t = t;
        edges.clear();
        for(auto& v : adj) v.clear();
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
    int n, m;
    cin >> n >> m;

    vector<pii> e;
    for(int i = 0;i < m;i++) {
        int p, q;
        cin >> p >> q;
        e.emplace_back(p, q);
    }

    Dinic dinic(n + 1, 0, 0);

    int ans = INT_MAX;
    for(int i = 1;i <= n;i++) {
        for(int j = i+1;j <= n;j++) {
            if(i == j) continue;
            dinic.reset(i, j);

            for(auto& p : e) {
                dinic.add_edge(p.first, p.second, 1);
                dinic.add_edge(p.second, p.first, 1);
            }
            ans = min(ans, dinic.flow());
        }
    }

    cout << ans << endl;
    return 0;
}
