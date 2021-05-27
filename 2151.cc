#include<iostream>
#include<queue>
#include<climits>
#include<algorithm>
using namespace std;
typedef struct {
	int x, y, dir;
}info;
info I;
queue<info> q;
char map[51][51];
int visit[51][51][4];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int n;
int result = INT_MAX, flag = 0;
int sx, sy, ex, ey;
void bfs() {
	for (int i = 0; i < 4; i++) {
		I = { sx,sy,i };
		q.push(I);
		visit[sx][sy][i] = 0;
	}
	int x, y, dir, nx, ny;
	while (!q.empty()) {
		x = q.front().x;
		y = q.front().y;
		dir = q.front().dir; q.pop();
		if (x == ex && y == ey) {
			result = min(result, visit[x][y][dir]);
			continue;
		}
		nx = x + dx[dir];
		ny = y + dy[dir];
		if (map[nx][ny] != '*' && visit[nx][ny][dir] > visit[x][y][dir]) {
			I = { nx,ny,dir };
			q.push(I);
			visit[nx][ny][dir] = visit[x][y][dir];
		}
		if (map[nx][ny] == '!') {
			if (dir < 2) {
				for (int i = 2; i < 4; i++) {
					if (visit[nx][ny][i] > visit[x][y][dir] + 1) {
						I = { nx,ny,i };
						q.push(I);
						visit[nx][ny][i] = visit[x][y][dir] + 1;
					}
				}
			}
			else {
				for (int i = 0; i < 2; i++) {
					if (visit[nx][ny][i] > visit[x][y][dir] + 1) {
						I = { nx,ny,i };
						q.push(I);
						visit[nx][ny][i] = visit[x][y][dir] + 1;
					}
				}
			}
		}
	}
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == '#') {
				if (!flag++) sx = i, sy = j;
				else ex = i, ey = j;
				map[i][j] = '.';
			}
			for (int k = 0; k < 4; k++)
				visit[i][j][k] = INT_MAX;
		}
	}
	bfs();
}