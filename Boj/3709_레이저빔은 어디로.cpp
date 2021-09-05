// https://www.acmicpc.net/problem/3709

#include<iostream>
#include<cstring>
#define mp make_pair
using namespace std;
int map[51][51];
bool visit[51][51][4];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int t, n, m, x, y;
pair<int, int> result;
pair<int, int> start() {
	int nx, ny, dir;
	if (1 > x) dir = 1;
	else if (x > n) dir = 3;
	else if (1 > y) dir = 0;
	else dir = 2;
	while (1) {
		nx = x + dx[dir];
		ny = y + dy[dir];
		if (1 > nx || nx > n || 1 > ny || ny > n) return mp(nx, ny);
		if (visit[nx][ny][dir]) return mp(0, 0);
		visit[nx][ny][dir] = 1;
		if (map[nx][ny] && ++dir > 3) dir = 0;
		x = nx;
		y = ny;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	while (t--) {
		cin >> n >> m;
		while (m--) {
			cin >> x >> y;
			map[x][y] = 1;
		}
		cin >> x >> y;
		result = start();
		cout << result.first << " " << result.second << "\n";
		memset(visit, 0, sizeof(visit));
		memset(map,0,sizeof(map));
	}
}
