#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
using namespace std;

string solve() {
    int n;
    cin >> n;

    vector<vector<int>> edge(n);
    vector<int> deg(n, 0);
    for(int i = 0;i < n-1;i++) {
        int p, q;
        cin >> p >> q;
        edge[p].emplace_back(q);
        edge[q].emplace_back(p);
        deg[p]++;
        deg[q]++;
    }

    int m;
    cin >> m;
    vector<int> key(m);
    for(int i = 0;i < m;i++) {
        cin >> key[i];
    }

    queue<pair<int, int>> que;
    for(int i = 0;i < n;i++) {
        if(deg[i] == 1) que.emplace(i, 0);
    }

    vector<int> deg_(deg);
    vector<set<int>> joint_len(n);
    vector<int> keys;
    int t = -1;
    while(!que.empty()) {
        auto x = que.front();
        que.pop();
        deg[x.first]--;
        for(auto y: edge[x.first]) {
            if(deg[y]) {
                deg[y]--;
                if(deg[y] == 1 && deg_[y] != 3) que.emplace(y, x.second + 1);
                if(deg_[y] == 3) {
                    joint_len[y].emplace(x.second + 1);
                    if(deg[y] == 1) t = y;
                }
            }
        }
    }

    int cur = t;
    keys.emplace_back(t);
    while(true) {
        deg[cur]--;
        int tmp = -1;
        for(auto y: edge[cur]) {
            if(deg[y]) {
                deg[y]--;
                tmp = y;

                if(deg_[y] == 3) keys.emplace_back(y);
            }
        }
        if(tmp == -1) break;
        cur = tmp;
    }

    int key_len = static_cast<int>(keys.size());
    int p = 0, q = 0;
    while(p < m && q < key_len && joint_len[keys[q]].count(key[p])) {
        p++, q++;
    }
    if(p == m && q == key_len) return "YES";

    p = 0, q = 0;
    reverse(keys.begin(), keys.end());
    while(p < m && q < key_len && joint_len[keys[q]].count(key[p])) {
        p++, q++;
    }
    if(p == m && q == key_len) return "YES";

    return "NO";
}

int main() {io
    cout << solve() << endl;
    return 0;
}