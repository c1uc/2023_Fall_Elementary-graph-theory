// 沒AC

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <set>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
#define MAX_N 100001
using namespace std;

int cal_dist(const string& a, const string& b) {
    for(unsigned k = 0;k < a.length();k++) {
        if(b.find(a.substr(k)) == 0) return b.length() - a.length() + k;
    }
    return b.length();
}

bool check_cont(vector<string>& vec, int n, int i) {
    for(int j = 0;j < n;j++) {
        if(j != i && vec[j].find(vec[i]) != string::npos) return true;
    }
    return false;
}

string dp(int n) {
    set<string> se;
    for(int i = 0;i < n;i++) {
        string ss;
        cin >> ss;
        se.emplace(ss);
    }

    vector<string> vec;
    vec.reserve(se.size());
    for(const auto & it : se) {
        vec.emplace_back(it);
    }

    vector<string> strings;
    for(int i = 0;i < n;i++) {
        if(!check_cont(vec, n, i)) {
            strings.emplace_back(vec[i]);
        }
    }

    n = strings.size();
    sort(strings.rbegin(), strings.rend());

    int dist[n][n];
    int mid[1 << n][n];
    int DP[1 << n][n];

    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) {
            dist[i][j] = cal_dist(strings[i], strings[j]);
            dist[j][i] = cal_dist(strings[j], strings[i]);
        }
    }

    for(int i = 1;i < (1 << n);i++) for(int j = 0;j < n;j++) DP[i][j] = MAX_N;

    int last = -1, min = MAX_N;
    for(int i = 1;i < (1 << n);i++) {
        for(int j = 0;j < n;j++) {
            if((i & (1 << j))) {
                int prev = i - (1 << j);

                if (prev == 0) DP[i][j] = strings[j].length();
                else {
                    for (int k = 0; k < n; k++) {
                        if (DP[prev][k] < MAX_N && DP[prev][k] + dist[k][j] < DP[i][j]) {
                            mid[i][j] = k;
                            DP[i][j] = DP[prev][k] + dist[k][j];
                        }
                    }
                }
            }
            if(i == (1 << n) - 1 && DP[i][j] < min) {
                min = DP[i][j], last = j;
            }
        }
    }

    int cur = (1 << n) - 1;
    stack<int> s;
    while(cur) {
        s.push(last);
        int tmp = cur;
        cur -= (1 << last);
        last = mid[tmp][last];
    }

    string ans;
    int i = s.top();
    ans += strings[i];
    s.pop();
    while(!s.empty()) {
        int j = s.top();
        s.pop();
        ans += strings[j].substr(strings[j].length() - dist[i][j]);
        i = j;
    }
    return ans;
}

int main() {io
    int n;
    cin >> n;
    cout << dp(n);
    return 0;
}