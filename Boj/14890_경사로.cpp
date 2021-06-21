// https://www.acmicpc.net/problem/14890

#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
int map[101][101];
bool visit[101][101];
int dx[2] = { 0,1 };
int dy[2] = { 1,0 };
int result = 0;
int n, l, x, y, nx, ny, temp;
void start(int sx, int sy, int dir) {
	x = sx, y = sy;
	memset(visit, 0, sizeof(visit));
	while (1) {
		nx = x + dx[dir];
		ny = y + dy[dir];
		if (1 > nx || nx > n || 1 > ny || ny > n) {
			++result;
			return;
		}
		if (map[x][y] != map[nx][ny]) {
			if (abs(map[nx][ny] - map[x][y]) != 1) return;
			else {
				if (map[x][y] < map[nx][ny]) {
					temp = map[x][y];
					for (int i = 0; i <= l - 1; i++) {
						if (1 > x - dx[dir] * i || x - dx[dir] * i > n || 1 > y - dy[dir] * i || y - dy[dir] * i > n) return;
						if (temp != map[x - dx[dir] * i][y - dy[dir] * i] || visit[x - dx[dir] * i][y - dy[dir] * i]) return;
					}
					for (int i = 0; i < l; i++)
						visit[x - dx[dir] * i][y - dy[dir] * i] = 1;
				}
				else {
					temp = map[nx][ny];
					for (int i = 0; i <= l - 1; i++) {
						if (1 > nx + dx[dir] * i || nx + dx[dir] * i > n || 1 > ny + dy[dir] * i || ny + dy[dir] * i > n) return;
						if (temp != map[nx + dx[dir] * i][ny + dy[dir] * i] || visit[nx + dx[dir] * i][ny + dy[dir] * i]) return;
					}
					for (int i = 0; i < l; i++)
						visit[nx + dx[dir] * i][ny + dy[dir] * i] = 1;
				}
			}
		}
		x = nx;
		y = ny;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> l;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (i == 1) start(i, j, 1);
			if (j == 1) start(i, j, 0);
		}
	}
	cout << result;
}
