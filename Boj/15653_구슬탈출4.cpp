// https://www.acmicpc.net/problem/15653

#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
typedef struct {
	int bx, by, rx, ry, cnt;
}info;
info I;
queue<info> q;
char map[11][11];
bool visit[11][11][11][11];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, sbx, sby, srx, sry;
int bfs() {
	I = { sbx,sby,srx,sry,0 };
	q.push(I);
	visit[sbx][sby][srx][sry] = 1;
	int bx, by, rx, ry, nbx, nby, nrx, nry, cnt, flag, stop, r_len, b_len;
	while (!q.empty()) {
		bx = q.front().bx;
		by = q.front().by;
		rx = q.front().rx;
		ry = q.front().ry;
		cnt = q.front().cnt; q.pop();
		if (map[rx][ry] == 'O' && map[bx][by] != 'O') return cnt;
		for (int dir = 0; dir < 4; ++dir) {
			stop = flag = 0;
			for (int i = 1;; ++i) {
				nbx = bx + dx[dir] * i;
				nby = by + dy[dir] * i;
				if (map[nbx][nby] == '#') {
					nbx -= dx[dir];
					nby -= dy[dir];
					break;
				}
				if (map[nbx][nby] == 'O') {
					flag = 1;
					break;
				}
			}
			if (flag) continue; //파란공이 빠져나간 경우 빨간공을 볼 필요도 없이 continue
			for (int i = 1;; ++i) {
				nrx = rx + dx[dir] * i;
				nry = ry + dy[dir] * i;
				if (map[nrx][nry] == '#') {
					nrx -= dx[dir];
					nry -= dy[dir];
					break;
				}
				if (map[nrx][nry] == 'O') {
					stop = 1;
					break;
				}
			}
			if (nrx == nbx && nry == nby) { //움직인 후 위치가 같다면, 움직이기 전의 위치를 비교 후 위치 재선언
				b_len = abs(nbx - bx) + abs(nby - by);
				r_len = abs(nrx - rx) + abs(nry - ry);
				if (r_len < b_len) nbx -= dx[dir], nby -= dy[dir];
				else nrx -= dx[dir], nry -= dy[dir];
			}
			if (!visit[nbx][nby][nrx][nry]) {
				I = { nbx,nby,nrx,nry,cnt + 1 };
				q.push(I);
				visit[nbx][nby][nrx][nry] = 1;
			}
			if (stop) break; //빨간공만 빠져나간 경우 바로 break
		}
	}
	return -1;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> map[i][j];
			if (map[i][j] == 'B') sbx = i, sby = j;
			else if (map[i][j] == 'R') srx = i, sry = j;
		}
	}
	map[sbx][sby] = map[srx][sry] = '.';
	cout << bfs();
}
