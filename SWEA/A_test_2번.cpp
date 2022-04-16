#include<iostream>
#include<queue>
#include<algorithm>
#include<climits>
#include<cstring>
using namespace std;
typedef struct {
	int x, y, max_h;
}info;
info I;
queue<info> q;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int map[51][51];
int visit[51][51][51]; // x, y, 현재까지 최대 높이
int t, n, m, start_x, start_y, dest_x, dest_y, result;
void q_push(int x, int y, int max_h) {
	I = { x,y,max_h };
	q.push(I);
	visit[x][y][max_h] = 1;
}
void bfs() {
	memset(visit, 0, sizeof(visit));
	q_push(start_x, start_y, 1);
	int jx, jy, tx, ty, jump, temp_max_h;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int max_h = q.front().max_h; q.pop();
		if (x == dest_x && y == dest_y) {
			result = min(result, max_h);
			continue;
		}
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m) {
				if (map[nx][ny]) {
					if (!visit[nx][ny][max_h])
						q_push(nx, ny, max_h);
				}
				else {
					if (i < 2) continue;
					tx = nx;
					ty = ny;
					jump = 1;
					while (1) {
						jx = tx + dx[i];
						jy = ty + dy[i];
						++jump;
						if (1 > jx || jx > n || 1 > jy || jy > m) break;
						if (map[jx][jy]) {
							temp_max_h = max(jump, max_h);
							if(!visit[jx][jy][temp_max_h])
								q_push(jx, jy, temp_max_h);
							break;
						}
						tx = jx;
						ty = jy;
					}
				}
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		cin >> n >> m;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				cin >> map[i][j];
				if (map[i][j] > 1) {
					if (map[i][j] == 2) start_x = i, start_y = j;
					else dest_x = i, dest_y = j;
					map[i][j] = 1;
				}
			}
		}
		result = INT_MAX;
		bfs();
		cout << "#" << l << " " << result << "\n";
	}
}
