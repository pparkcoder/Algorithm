//https://www.acmicpc.net/problem/3197
//TLE -> 백조 bfs 수행 시(meet 함수) 계속적인 visit 배열 초기화
//Solving -> 백조가 한번 간 곳은 방문처리 후 초기화 필요x -> 얼음이 녹으면 현재 위치에서 갈 수 잇는 길이 또 생기므로 + 전에 갔던 곳은 갈 필요X
//Tip -> queue 복사 시, 직접 넣거나 q = q2 보다 swap을 이용하면 시간 절약 -> 저장될 큐.swap(옮길 데이터가 있는 큐)

#include<iostream>
#include<queue>
#include<algorithm>
#include<cstring>
#define mp make_pair
using namespace std;
queue<pair<int, int> > q, now_p, next_p;
char map[1501][1501];
bool visit[1501][1501];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int r, c, sx, sy, ex, ey;
bool meet() {
	//memset(visit, 0, sizeof(visit)); TLE 원인
	int x, y, nx, ny;
	now_p.push(mp(sx, sy));
	visit[sx][sy] = 1;
	while (!now_p.empty()) {
		x = now_p.front().first;
		y = now_p.front().second; now_p.pop();
		for (int i = 0; i < 4; ++i) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (0 < nx && nx <= r && 0 < ny && ny <= c) {
				if (nx == ex && ny == ey) return true;
				if (map[nx][ny] == '.' && !visit[nx][ny]) {
					now_p.push(mp(nx, ny));
					next_p.push(mp(nx, ny));
					visit[nx][ny] = 1;
				}
			}
		}
	}
	now_p.swap(next_p);
	while (!next_p.empty()) next_p.pop();
	return false;
}
void start() {
	int x, y, nx, ny, len;
	for (int i = 0;; ++i) {
		if (meet()) {
			cout << i;
			return;
		}
		len = q.size();
		while (len--) {
			x = q.front().first;
			y = q.front().second; q.pop();
			for (int j = 0; j < 4; ++j) {
				nx = x + dx[j];
				ny = y + dy[j];
				if (0 < nx && nx <= r && 0 < ny && ny <= c && map[nx][ny] == 'X') {
					q.push(mp(nx, ny));
					map[nx][ny] = '.';
				}
			}
		}
	}
	return;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int flag = 0;
	cin >> r >> c;
	for (int i = 1; i <= r; ++i) {
		for (int j = 1; j <= c; ++j) {
			cin >> map[i][j];
			if (map[i][j] == 'L') {
				if (!flag++) sx = i, sy = j;
				else ex = i, ey = j;
				map[i][j] = '.';
			}
			if (map[i][j] == '.')
				q.push(mp(i, j));
		}
	}
	start();
}
