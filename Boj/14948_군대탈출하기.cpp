// https://www.acmicpc.net/problem/14948

#include<iostream>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;
typedef struct {
	int x, y, max_num, flag;
}info;
info I;
queue<info> q;
int map[101][101];
int visit[101][101][2];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, result;
void check(int x, int y, int max_num, int flag) {
	if (visit[x][y][flag] == INT_MAX) {
		if (max_num < map[x][y]) {
			I = { x,y,map[x][y],flag };
			q.push(I);
			visit[x][y][flag] = map[x][y];
		}
		else {
			I = { x,y,max_num,flag };
			q.push(I);
			visit[x][y][flag] = max_num;
		}
	}
	else {
		int temp = max(max_num, map[x][y]);
		if (visit[x][y][flag] > temp) {
			I = { x,y,temp,flag };
			q.push(I);
			visit[x][y][flag] = temp;
		}
	}
}
void bfs() {
	I = { 0,0,map[0][0],0 };
	q.push(I);
	visit[0][0][0] = map[0][0];
	while (!q.empty()) {
		int x = q.front().x;
		int y = q.front().y;
		int max_num = q.front().max_num;
		int flag = q.front().flag; q.pop();
		if (x == n - 1 && y == m - 1) continue;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 <= nx && nx < n && 0 <= ny && ny < m) check(nx, ny, max_num, flag);
			if (!flag) {
				int nnx = nx + dx[i];
				int nny = ny + dy[i];
				if (0 <= nnx && nnx < n && 0 <= nny && nny < m) check(nnx, nny, max_num, 1);
			}
		}
	}
	cout << (result = min(visit[n - 1][m - 1][0], visit[n - 1][m - 1][1]));
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			visit[i][j][0] = visit[i][j][1] = INT_MAX;
		}
	}
	bfs();
}
