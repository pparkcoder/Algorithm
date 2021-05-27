/*1194 달이 차오른다 가자
https://www.acmicpc.net/problem/1194*/

#include<iostream>
#include<queue>
#include<climits>
using namespace std;
typedef struct {
	int x, y, key;
}info;
info I;
queue<info> q;
char map[51][51];
int dist[51][51][64];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, sx, sy;
int bfs() {
	I = { sx,sy,0 };
	q.push(I);
	dist[sx][sy][0] = 0;
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int key = q.front().key; q.pop();
		if (map[x][y] == '1') return dist[x][y][key];
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m && map[nx][ny] != '#') {
				if ('A' <= map[nx][ny] && map[nx][ny] <= 'F') {
					if (key & 1 << (map[nx][ny] - 'A') && dist[nx][ny][key] > dist[x][y][key] + 1) {
						I = { nx,ny,key };
						q.push(I);
						dist[nx][ny][key] = dist[x][y][key] + 1;
					}
				}
				else if ('a' <= map[nx][ny] && map[nx][ny] <= 'f') {
					int new_key = key | 1 << (map[nx][ny] - 'a');
					if (dist[nx][ny][new_key] > dist[x][y][key] + 1) {
						I = { nx,ny,new_key };
						q.push(I);
						dist[nx][ny][new_key] = dist[x][y][key] + 1;
					}

				}
				else if (map[nx][ny] == '.' || map[nx][ny] == '1') {
					if (dist[nx][ny][key] > dist[x][y][key] + 1) {
						I = { nx,ny,key };
						q.push(I);
						dist[nx][ny][key] = dist[x][y][key] + 1;
					}
				}
			}
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			if (map[i][j] == '0') {
				sx = i;
				sy = j;
				map[i][j] = '.';
			}
			for (int k = 0; k < 64; k++)
				dist[i][j][k] = INT_MAX;
		}
	}
	cout << bfs();
}
