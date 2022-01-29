#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>
#define mp make_pair
using namespace std;
vector<pair<int, int> >v;
int map[13][13];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int result_len, result_core, t, n;
int make_len(int now_x, int now_y, int dir) {
    int nx, ny;
    int cnt_len = 0;
    for (int i = 1;; ++i) {
        nx = now_x + dx[dir] * i;
        ny = now_y + dy[dir] * i;
        if (0 < nx && nx <= n && 0 < ny && ny <= n) {
            if (!map[nx][ny]) ++cnt_len;
            else return -1;
        }
        else return cnt_len;
    }
}
void brute(int cnt_core, int cnt_len, int index) {
    if (index == v.size()) {
        if (result_core <= cnt_core) {
            if (result_core != cnt_core) result_len = cnt_len;
            else result_len = min(result_len, cnt_len);
            result_core = cnt_core;
        }
        return;
    }
    int x, y, temp;
    for (int i = index; i < v.size(); ++i) {
        x = v[i].first;
        y = v[i].second;
        for (int j = 0; j < 4; ++j) {
            temp = make_len(x, y, j);
            if (temp != -1) {
                for (int k = 1; k <= temp; ++k) map[x + dx[j] * k][y + dy[j] * k] = 2;
                brute(cnt_core + 1, cnt_len + temp, i + 1);
                for (int k = 1; k <= temp; ++k) map[x + dx[j] * k][y + dy[j] * k] = 0;
            }
        }
    }
}
void init() {
    result_len = INT_MAX;
    result_core = -INT_MAX;
    v.clear();
}
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> t;
    for (int l = 1; l <= t; ++l) {
        cin >> n;
        init();
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                cin >> map[i][j];
                if (map[i][j]) {
                    if (i == 1 || i == n || j == 1 || j == n) continue;
                    v.push_back(mp(i, j));
                }
            }
        }
        brute(0, 0, 0);
        cout << "#" << l << " " << result_len << "\n";
    }
}
