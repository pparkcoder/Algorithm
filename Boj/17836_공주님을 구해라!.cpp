#include<iostream>
#include<cstring>
#include<queue>
#include<climits>
using namespace std;
typedef struct {
	int x, y, flag, cnt;
}info;
info I;
queue<info> q;
int map[101][101];
int visit[101][101][2];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, t, result;
void q_push(int x, int y, int nx, int ny, int flag) {
	I = { nx,ny,flag,visit[x][y][flag] + 1 };
	q.push(I);
	visit[nx][ny][flag] = visit[x][y][flag] + 1;
}
int start() {
	int x, y, flag, cnt, nx, ny;
	I = { 1,1,0,0 };
	q.push(I);
	visit[1][1][0] = 1;
	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		flag = q.front().flag;
		cnt = q.front().cnt; q.pop();
		if (x == n && y == m) return cnt - 1;
		for (int i = 0; i < 4; ++i) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m) {
				if (map[nx][ny] == 1) {
					if (flag && visit[x][y][flag] + 1 < visit[nx][ny][flag]) {
						q_push(x, y, nx, ny, flag);
					}
				}
				else if (map[nx][ny] == 2) {
					if (flag && visit[x][y][flag] + 1 < visit[nx][ny][flag]) {
						q_push(x, y, nx, ny, flag);
					}
					else if (!flag && visit[x][y][flag] + 1 < visit[nx][ny][flag + 1]) {
						I = { nx,ny,flag + 1,visit[x][y][flag] + 1 };
						q.push(I);
						visit[nx][ny][flag + 1] = visit[x][y][flag] + 1;
					}
				}
				else {
					if (visit[x][y][flag] + 1 < visit[nx][ny][flag]) {
						q_push(x, y, nx, ny, flag);
					}
				}
			}
		}
	}
	return INT_MAX;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> t;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> map[i][j];
			for (int k = 0; k < 2; ++k)
				visit[i][j][k] = INT_MAX;
		}
	}
	result = start();
	result > t ? cout << "Fail" : cout << result;
}
