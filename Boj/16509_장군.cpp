// https://www.acmicpc.net/problem/16509

#include<iostream>
#include<queue>
using namespace std;
typedef struct {
	int x, y, cnt;
}info;
info I;
queue<info> q;
bool visit[10][9];
int dx[8][3] = { {-1,-1,-1},{0,-1,-1},{0,1,1},{1,1,1},{1,1,1},{0,1,1},{0,-1,-1},{-1,-1,-1} };
int dy[8][3] = { {0,1,1},{1,1,1},{1,1,1},{0,1,1},{0,-1,-1},{-1,-1,-1},{-1,-1,-1},{0,-1,-1} };
int sx, sy, ex, ey;
int bfs() {
	I = { sx,sy,0 };
	q.push(I);
	visit[sx][sy] = 1;
	int x, y, nx, ny,tx,ty, cnt, flag;
	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		cnt = q.front().cnt; q.pop();
		if (x == ex && y == ey) return cnt;
		for (int i = 0; i < 8; ++i) {
			tx = x;
			ty = y;
			flag = 0;
			for (int j = 0; j < 3; ++j) {
				nx = tx + dx[i][j];
				ny = ty + dy[i][j];
				if (0 > nx || nx > 9 || 0 > ny || ny > 8 || (j < 2 && nx == ex && ny == ey)) {
					flag = 1;
					break;
				}
				tx = nx;
				ty = ny;
			}
			if (flag || visit[nx][ny]) continue;
			I = { nx,ny,cnt + 1 };
			q.push(I);
			visit[nx][ny] = 1;
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> sx >> sy >> ex >> ey;
	cout << bfs();
}
