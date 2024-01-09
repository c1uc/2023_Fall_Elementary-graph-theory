#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <algorithm>
#include <set>
#define io std::ios::sync_with_stdio(false);std::cin.tie(0);
#define MAX_N 100001
using namespace std;

int best = MAX_N;
string best_res;

string construct_string(vector<string>& strings, vector<int>& path, int** dist) {
    string res = strings[path[0]];
    for(int i = 1;i < path.size();i++) {
        res += strings[path[i]].substr(strings[path[i]].length() - dist[path[i - 1]][path[i]]);
    }
    return res;
}

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

void DFS(vector<string>& vec, vector<int> path, int idx, int** dist, set<int>& used, int cur) {
    if(cur > best) return;
    if(idx == vec.size()) {
        string res = construct_string(vec, path, dist);
        if((best_res.empty() || res < best_res)) {
            best_res = res;
            best = cur;
        }
    } else {
        for(int i = 0;i < vec.size();i++) {
            if(used.count(i)) continue;
            path[idx] = i;
            used.emplace(i);
            if(idx == 0) DFS(vec, path, idx+1, dist, used, vec[i].length());
            else DFS(vec, path, idx+1, dist, used, cur + dist[path[idx-1]][i]);
            used.erase(i);
        }
    }
}


string solve(int n) {
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

    n = vec.size();
    vector<string> strings;
    for(int i = 0;i < n;i++) {
        if(!check_cont(vec, n, i)) {
            strings.emplace_back(vec[i]);
        }
    }

    n = strings.size();
    sort(strings.rbegin(), strings.rend());

    int** dist = new int*[n];

    for(int i = 0;i < n;i++) dist[i] = new int[n];

    for(int i = 0;i < n;i++) {
        for(int j = 0;j < n;j++) {
            dist[i][j] = cal_dist(strings[i], strings[j]);
            dist[j][i] = cal_dist(strings[j], strings[i]);
        }
    }

    vector<int> path(n);
    set<int> used;
    DFS(strings, path, 0, dist, used, 0);
    return best_res;
}

int main() {io
    int n;
    cin >> n;
    cout << solve(n);
    return 0;
}