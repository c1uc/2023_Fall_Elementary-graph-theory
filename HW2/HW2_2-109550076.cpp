#include <iostream>
#include <vector>
#include <queue>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
#define MAX_N 1001
using namespace std;

int solve(int n) {
    vector<vector<int>> edge(n+1);
    for(int i = 0;i < n-1;i++) {
        int p, q;
        cin >> p >> q;
        edge[p].emplace_back(q);
        edge[q].emplace_back(p);
    }

    queue<int> que;
    vector<pair<bool, int>> vis(n+1, make_pair(false, 0));
    vis[1] = make_pair(true, 0);
    que.push(1);
    int last = -1, diameter = -1;

    while(!que.empty()) {
        int x = que.front();
        last = x;
        que.pop();

        for(auto i: edge[x]) {
            if(!vis[i].first) { que.push(i); vis[i] = make_pair(true, vis[x].second+1); }
        }
    }

    fill(vis.begin(), vis.end(), make_pair(false, 0));
    que.push(last);
    vis[last] = make_pair(true, 0);

    while(!que.empty()) {
        int x = que.front();
        diameter = vis[x].second;
        que.pop();

        for(auto i: edge[x]) {
            if(!vis[i].first) { que.push(i); vis[i] = make_pair(true, vis[x].second+1); }
        }
    }
    return diameter;
}

int main() {io
    int n;
    cin >> n;
    cout << solve(n);
    return 0;
}