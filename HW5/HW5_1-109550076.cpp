#include<bits/stdc++.h>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
using namespace std;

typedef pair<int, int> pii;

bool contain_K33(const vector<vector<int>>& e, vector<int>& idx) {
    if(idx.size() != 6) return false;

    do {
        bool flag = true;

        for(int i = 0;i < 3;i++) {
            for(int j = i+1;j < 3;j++) {
                if(e[idx[i]][idx[j]]) flag = false;
                if(!flag) break;
            }
            if(!flag) break;
        }
        if(!flag) continue;

        for(int i = 3;i < 6;i++) {
            for(int j = i+1;j < 6;j++) {
                if(e[idx[i]][idx[j]]) flag = false;
                if(!flag) break;
            }
        }
        if(!flag) continue;

        for(int i = 0;i < 3;i++) {
            for(int j = 3;j < 6;j++) {
                if(!e[idx[i]][idx[j]]) flag = false;
                if(!flag) break;
            }
            if(!flag) break;
        }

        if(flag) return true;
    } while(next_permutation(idx.begin(), idx.end()));

    return false;
}

bool contain_K5(const vector<vector<int>>& e, vector<int>& idx) {
    if(idx.size() != 5) return false;

    do {
        bool flag = true;

        for(int i = 0;i < 5;i++) {
            for(int j = i+1;j < 5;j++) {
                if(!e[idx[i]][idx[j]]) flag = false;

                if(!flag) break;
            }
            if(!flag) break;
        }

        if(flag) return true;
    } while(next_permutation(idx.begin(), idx.end()));

    return false;
}

void connect_subdivision(vector<vector<int>>& e, vector<int>& deg) {
    const int n = static_cast<int>(deg.size()) - 1;
    while(true) {
        bool flag = true;

        for(int i = 1;i <= n;i++) {
            if(deg[i] == 2) {
                int p = -1, q = -1;
                for(int j = 1;j <= n;j++) {
                    if(e[i][j]) {
                        if(p == -1) p = j;
                        else q = j;
                    }
                }

                e[i][p] = 0;
                e[p][i] = 0;

                e[i][q] = 0;
                e[q][i] = 0;

                if(e[p][q]) {
                    deg[p]--;
                    deg[q]--;
                }

                e[p][q] = 1;
                e[q][p] = 1;

                deg[i] = 0;

                flag = false;
                break;
            }
        }

        if(flag) break;
    }
}

bool solve() {
    int n, m;
    cin >> n >> m;
    vector<pii> e;

    for(int i = 0;i < m;i++) {
        int p, q;
        cin >> p >> q;
        e.emplace_back(p, q);
    }

    vector<vector<int>> ee;
    vector<int> deg;
    for(int t = 1;t < (1 << m);t++) {
        ee.clear();
        ee.resize(n + 1, vector<int>(n + 1, 0));

        deg.clear();
        deg.resize(n + 1, 0);

        for(int i = 0;i < m;i++) {
            if(t & (1 << i)) {
                ee[e[i].first][e[i].second] = 1;
                ee[e[i].second][e[i].first] = 1;

                deg[e[i].first]++;
                deg[e[i].second]++;
            }
        }

        connect_subdivision(ee, deg);

        // K33
        vector<int> idx;
        for(int i = 1;i <= n;i++) {
            if(deg[i] == 3) idx.emplace_back(i);
        }
        if(contain_K33(ee, idx)) return true;

        // K5
        idx.clear();
        for(int i = 1;i <= n;i++) {
            if(deg[i] == 4) idx.emplace_back(i);
        }
        if(contain_K5(ee, idx)) return true;
    }
    return false;
}

int main() {io
    int q;
    cin >> q;
    while(q--) {
        if(solve()) cout << "No\n";
        else cout << "Yes\n";
    }
    return 0;
}
