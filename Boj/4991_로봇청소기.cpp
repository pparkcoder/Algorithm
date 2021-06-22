// https://www.acmicpc.net/problem/4991

#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
typedef struct {
	int x, y, cnt, key;
}info;
info I;
queue<info> q;
char map[21][21];
bool visit[21][21][1024];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int w, h, sx, sy, item_cnt;
int bfs() {
	while (!q.empty()) q.pop();
	I = { sx,sy,0,0 };
	q.push(I);
	visit[sx][sy][0] = 1;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int cnt = q.front().cnt;
		int key = q.front().key; q.pop();
		if (key == item_cnt) return cnt;
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= h && 0 < ny && ny <= w) {
				if (map[nx][ny] == '.' && !visit[nx][ny][key]) {
					I = { nx,ny,cnt + 1,key };
					q.push(I);
					visit[nx][ny][key] = 1;
				}
				else if ('A' <= map[nx][ny] && map[nx][ny] <= 'Z') {
					if (key & 1 << (map[nx][ny] - 'A')) {
						if (!visit[nx][ny][key]) {
							I = { nx,ny,cnt + 1,key };
							q.push(I);
							visit[nx][ny][key] = 1;
						}
					}
					else {
						int new_key = key | 1 << (map[nx][ny] - 'A');
						if (!visit[nx][ny][new_key]) {
							I = { nx,ny,cnt + 1,new_key };
							q.push(I);
							visit[nx][ny][new_key] = 1;
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
	while (1) {
		cin >> w >> h;
		if (!w && !h) break;
		item_cnt = 0;
		for (int i = 1; i <= h; ++i) {
			for (int j = 1; j <= w; ++j) {
				cin >> map[i][j];
				if (map[i][j] == 'o') {
					sx = i, sy = j;
					map[i][j] = '.';
				}
				else if (map[i][j] == '*')
					map[i][j] = 'A' + item_cnt++;
				for (int k = 0; k < 1024; ++k)
					visit[i][j][k] = 0;
			}
		}
		item_cnt = (1 << item_cnt) - 1;
		cout << bfs() << "\n";
	}
}
