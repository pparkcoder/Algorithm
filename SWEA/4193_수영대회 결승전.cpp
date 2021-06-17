// 시간이 기준이 아닌 step이 기준
// TLE -> 소용돌이를 못 건너는 경우 그 자리를 다시 puth
// Solving -> 소용돌이를 못 건너는 경우 그 자리를 다시 '한번만' 넣어주고 pass

#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
typedef struct {
	int x, y, cnt, step;
}info;
info I;
queue<info> q;
int map[15][15];
bool visit[15][15];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int t, n, sx, sy, ex, ey;

int bfs() {
	while (!q.empty()) q.pop();
	memset(visit, 0, sizeof(visit));
	I = { sx,sy,0,1 };
	q.push(I);
	visit[sx][sy] = 1;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int cnt = q.front().cnt;
		int step = q.front().step; q.pop();
		int flag = 0;
		if (x == ex && y == ey) return cnt;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 <= nx && nx < n && 0 <= ny && ny < n && !visit[nx][ny]) {
				if (!map[nx][ny]) {
					I = { nx,ny,cnt + 1,step + 1 };
					q.push(I);
					visit[nx][ny] = 1;
				}
				else if (map[nx][ny] == 2) {
					if (!(step % 3)) {
						I = { nx,ny,cnt + 1,1 };
						q.push(I);
						flag = visit[nx][ny] = 1;
					}
					else {
						if (!flag) {
							I = { x,y,cnt + 1,step + 1 };
							q.push(I);
							flag = 1;
						}
					}
				}
			}
		}
	}
	return -1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		cin >> n;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> map[i][j];
		cin >> sx >> sy >> ex >> ey;
		cout << "#" << l << " " << bfs() << "\n";
	}
}
