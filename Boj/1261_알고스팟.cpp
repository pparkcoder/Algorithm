// https://www.acmicpc.net/problem/1261

#include<iostream>
#include<deque>
#include<algorithm>
#include<climits>
#define mp make_pair
using namespace std;
deque<pair<int, int> > q;
char map[101][101];
int visit[101][101];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m;
int result = INT_MAX;
void bfs() {
	q.push_back(mp(1, 1));
	visit[1][1] = 0;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop_front();
		if (x == n && y == m) {
			result = min(result, visit[x][y]);
			continue;
		}
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m) {
				if (map[nx][ny] == '0' && visit[nx][ny] > visit[x][y]) {
					q.push_front(mp(nx, ny));
					visit[nx][ny] = visit[x][y];

				}
				else if (map[nx][ny] == '1' && visit[nx][ny] > visit[x][y] + 1) {
					q.push_back(mp(nx, ny));
					visit[nx][ny] = visit[x][y] + 1;
				}
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> m >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> map[i][j];
			visit[i][j] = INT_MAX;
		}
	}
	bfs();
	cout << result;
}
