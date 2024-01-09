#include <iostream>
#include <cstring>
using namespace std;

int main() {
    int n, m, p, q, r;
    cin >> n >> m;
    int a[n + 1][n + 1];
    memset(a, 0, sizeof(a));
    int b[n + 1][2];
    memset(b, 0, sizeof(b));
    while(m--) {
        cin >> p >> q >> r;
        a[p][q] = r;
        b[p][0]++;
        b[q][1]++;
    }
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= n;j++) {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
    for(int i = 1;i <= n;i++) {
        cout << b[i][1] << ' ' << b[i][0] << endl;
    }
    return 0;
}