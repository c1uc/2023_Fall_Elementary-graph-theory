#include <iostream>
#include <map>
using namespace std;

int main() {
    map<int, int> mm;
    int n, i, maxc = 0, ans;
    cin >> n;
    while(n--) {
        cin >> i;
        mm[i]++;
    }
    for(auto it: mm) {
        if(it.second >= maxc) maxc = it.second, ans = it.first;
    }
    cout << ans << " " << maxc << '\n';
    return 0;
}