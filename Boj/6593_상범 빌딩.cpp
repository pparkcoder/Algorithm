// https://www.acmicpc.net/problem/6593

#include<iostream>
#include<queue>
#define mp make_pair
using namespace std;
typedef struct {
	int h, x, y;
}info;
info I;
queue<info>q;
char map[31][31][31];
int visit[31][31][31];
int dh[6] = { -1,1,0,0,0,0 };
int dx[6] = { 0,0,0,0,-1,1 };
int dy[6] = { 0,0,-1,1,0,0 };
int l, r, c, sh, sx, sy;
int bfs() {
	while (!q.empty()) q.pop();
	I = { sh,sx,sy };
	q.push(I);
	visit[sh][sx][sy] = 1;
	while (!q.empty()) {
		int h = q.front().h;
		int x = q.front().x;
		int y = q.front().y; q.pop();
		if (map[h][x][y] == 'E') return visit[h][x][y] - 1;
		for (int i = 0; i < 6; i++) {
			int nh = h + dh[i];
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nh && nh <= l && 0 < nx && nx <= r && 0 < ny && ny <= c && map[nh][nx][ny] != '#' && !visit[nh][nx][ny]) {
				I = { nh,nx,ny };
				q.push(I);
				visit[nh][nx][ny] = visit[h][x][y] + 1;
			}
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	while (1) {
		cin >> l >> r >> c;
		if (!l && !r && !c) break;
		for (int i = 1; i <= l; i++) {
			for (int j = 1; j <= r; j++) {
				for (int k = 1; k <= c; k++) {
					cin >> map[i][j][k];
					if (map[i][j][k] == 'S') sh = i, sx = j, sy = k;
					visit[i][j][k] = 0;
				}
			}
		}
		int result = bfs();
		if (result == -1) cout << "Trapped!";
		else cout << "Escaped in " << result << " minute(s).";
		cout << "\n";
	}
}
