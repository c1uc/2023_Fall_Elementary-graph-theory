#include <iostream>
#include <vector>
using namespace std;
#define MAXN 200001

vector<int> a[MAXN];
int c[MAXN];
int N;

int dfs(int x, int v) {
    c[x] = v;
    for(int i: a[x]) {
        if(c[i] == v) return 1;
        if(!c[i])
            dfs(i, -v);
    }
    return 0;
}

int main() {
    int m, p, q;
    cin >> N >> m;
    
    while(m--) {
        cin >> p >> q;
        a[p].emplace_back(q);
        a[q].emplace_back(p);
    }
    for(int i = 1;i <= N;i++) {
        if(!c[i])
            if(dfs(i, 1)) {
                cout << "No" << endl;
                return 0;
            }
    }
    cout << "Yes" << endl;
    return 0;
}