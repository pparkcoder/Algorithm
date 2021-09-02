// https://www.acmicpc.net/problem/2573

#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#define mp make_pair
using namespace std;
typedef struct {
	int x, y, cnt;
}info;
info I;
queue<pair<int, int> > q, q2;
vector<info> v;
int map[301][301];
bool visit[301][301];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m;
int stop = 0, result = 0;
void bfs(int sx, int sy, int flag) {
	if (flag) {
		q.push(mp(sx, sy));
		visit[sx][sy] = 1;
	}
	else {
		while (!q2.empty()) {
			q.push(mp(q2.front().first, q2.front().second));
			q2.pop();
		}
	}
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		int cnt = 0;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m) {
				if (!flag && !map[nx][ny]) ++cnt;
				else if (flag && map[nx][ny] && !visit[nx][ny]) {
					q.push(mp(nx, ny));
					visit[nx][ny] = 1;
				}
			}
		}
		if (!flag) {
			I = { x,y,cnt };
			v.push_back(I);
		}
	}
	if (!flag) {
		for (int i = 0; i < v.size(); ++i) {
			int x = v[i].x;
			int y = v[i].y;
			int cnt = v[i].cnt;
			map[x][y] = (map[x][y] - cnt <= 0 ? 0 : map[x][y] - cnt);
			if (map[x][y]) q2.push(mp(x, y));
		}
		if (q2.empty()) stop = 1;
		v.clear();
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> map[i][j];
			if (map[i][j]) q.push(mp(i, j));
		}
	}
	for (int i = 1;; ++i) {
		bfs(0, 0, 0);
		if (stop) break;
		int cnt = 0;
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= m; ++k) {
				if (map[j][k] && !visit[j][k]) {
					bfs(j, k, 1);
					++cnt;
				}
			}
		}
		if (cnt > 1) {
			result = i;
			break;
		}
		memset(visit, 0, sizeof(visit));
	}
	cout << result;
}
