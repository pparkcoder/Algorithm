// https://www.acmicpc.net/problem/3108

#include<iostream>
#include<queue>
#define mp make_pair
using namespace std;
queue<pair<int, int> >q;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int map[2001][2001];
bool visit[2001][2001];
int n;
int result = 0, check = 0, sx = 1000, sy = 1000;
void draw(int x1,int y1,int x2,int y2) {
	for (int i = y1; i <= y2; i++)
		map[x1][i] = 1;
	for (int i = y1; i <= y2; i++)
		map[x2][i] = 1;
	for (int i = x1; i <= x2; i++)
		map[i][y1] = 1;
	for (int i = x1; i <= x2; i++)
		map[i][y2] = 1;
}
void bfs(int start_x, int start_y) {
	q.push(mp(start_x, start_y));
	visit[start_x][start_y] = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 <= nx && nx <= 2000 && 0 <= ny && ny <= 2000) {
				if (map[nx][ny] && !visit[nx][ny]) {
					q.push(mp(nx, ny));
					visit[nx][ny] = 1;
				}
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n;
	int x1, y1, x2, y2;
	while (n--) {
		cin >> y1 >> x1 >> y2 >> x2;
		draw((x1 + 500) * 2, (y1 + 500) * 2, (x2 + 500) * 2, (y2 + 500) * 2);
	}
	if (map[sx][sy]) bfs(sx, sy);
	for (int i = 0; i <= 2000; i++) {
		for (int j = 0; j <= 2000; j++) {
			if (map[i][j] && !visit[i][j]) {
				++result;
				bfs(i, j);
			}
		}
	}
	cout << result;
}
