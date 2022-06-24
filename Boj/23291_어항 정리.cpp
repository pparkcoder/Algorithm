// https://www.acmicpc.net/problem/23291

#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>
#include<cstring>
#define mp make_pair
using namespace std;
vector<pair<int, int> > v, v2;
int map[101][101];
int memo[101][101];
bool visit[101][101];
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int n, k;
bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.second == b.second) return a.first < b.first;
    else return a.second < b.second;
}
void turn() {
    vector<int> temp;
    int index;
    for (int i = (n / 2); i > 0; --i) {
        temp.push_back(map[n][i]);
        map[n][i] = 0;
    }
    index = 0;
    for (int i = (n / 2) + 1; i <= n; ++i)
        map[n - 1][i] = temp[index++];
    temp.clear();
    for (int i = 1; i >= 0; --i) {
        for (int j = (n / 2) + (n / 4); j > (n / 2); --j) {
            temp.push_back(map[n - i][j]);
            map[n - i][j] = 0;
        }
    }
    index = 0;
    for (int i = 2; i < 4; ++i) {
        for (int j = (n / 2) + (n / 4) + 1; j <= n; ++j) {
            map[n - i][j] = temp[index++];
        }
    }
}
void clean() {
    vector<pair<int, int> > temp;
    vector<int> temp2;
    memset(memo, 0, sizeof(memo));
    int x, y, nx, ny, d, index;
    // 물고기 수 조절
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (map[i][j]) {
                temp.push_back(mp(i, j));
                for (int len = 0; len < 4; ++len) {
                    nx = i + dx[len];
                    ny = j + dy[len];
                    if (0 < nx && nx <= n && 0 < ny && ny <= n && map[nx][ny]) {
                        d = (map[i][j] - map[nx][ny]) / 5;
                        if (d > 0) memo[i][j] -= d, memo[nx][ny] += d;
                    }
                }
            }
        }
    }
    for (int i = 0; i < temp.size(); ++i) {
        x = temp[i].first;
        y = temp[i].second;
        map[x][y] += memo[x][y];
    }
    // 일렬로 정렬
    for (int i = 1; i <= n; ++i) {
        if (map[n][i]) {
            for (int j = n; j > 0; --j) {
                if (!map[j][i]) break;
                temp2.push_back(map[j][i]);
                map[j][i] = 0;
            }
        }
    }
    index = 0;
    for (int i = 1; i <= n; ++i)
        map[n][i] = temp2[index++];
}
void stack() {
    memset(visit, 0, sizeof(visit));
    v.clear();
    v.push_back(mp(n, 1));
    visit[n][1] = 1;
    int x, y, nx, ny, sx, sy, pre_y, index;
    for (int turn = 1;; ++turn) {
        for (int i = 0; i < v.size(); ++i) {
            sy = v[i].second;
            if (!visit[n][sy]) {
                v.push_back(mp(n, sy));
                visit[n][sy] = 1;
            }
        }
        sort(v.begin(), v.end(), cmp);
        index = 0;
        pre_y = v[0].second;
        sx = v[0].first;
        sy = v[0].second + turn;
        if (sy > n) return; // 종료 조건
        if (turn % 2) --sx;
        for (int i = 0; i < v.size(); ++i) {
            x = v[i].first;
            y = v[i].second;
            if (pre_y == v[i].second) {
                nx = sx;
                ny = sy - (index++);
            } else {
                pre_y = v[i].second;
                ++sx;
                index = 0;
                --i;
                continue;
            }
            v2.push_back(mp(nx, ny));
            map[nx][ny] = map[x][y];
            map[x][y] = 0;
        }
        v = v2;
        v2.clear();
    }
}
void find_min() {
    int min_num = INT_MAX;
    for (int i = 1; i <= n; ++i) 
        if (map[n][i] < min_num) min_num = map[n][i];
    for (int i = 1; i <= n; ++i) 
        if (map[n][i] == min_num) ++map[n][i];
}
bool check() {
    int min_num = INT_MAX, max_num = 0;
    for (int i = 1; i <= n; ++i) {
        if (map[n][i] > max_num) max_num = map[n][i];
        if (map[n][i] < min_num) min_num = map[n][i];
    }
    if (max_num - min_num <= k) return true;
    else return false;
}
int start() {
    for (int i = 1;; ++i) {
        find_min();
        stack();
        clean();
        turn();
        clean();
        if (check()) return i;
    }
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0);
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> map[n][i];
    }
    cout << start();
}
