// https://www.acmicpc.net/problem/23288

#include<iostream>
#include<algorithm>
#include<queue>
#include<cstring>
#define mp make_pair
using namespace std;
queue<pair<int, int> > q;
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int map[4][3] = { {0,2,0},
				  {4,1,3},
				  {0,5,0},
				  {0,6,0} };
int board[21][21];
bool visit[21][21];
int result = 0;
int n, m, t, max_cnt;
int bfs(int sx,int sy,int num) {
	while (!q.empty()) q.pop();
	memset(visit, 0, sizeof(visit));
	q.push(mp(sx, sy));
	visit[sx][sy] = 1;
	int cnt = 1;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;q.pop();
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m && !visit[nx][ny] && board[nx][ny] == num) {
				q.push(mp(nx, ny));
				visit[nx][ny] = 1;
				++cnt;
			}
		}
	}
	return cnt;
}
void make_dice(int dir) {
	int temp;
	if (dir == 0) {
		temp = map[0][1];
		for (int i = 1; i <= 3; ++i)
			map[i - 1][1] = map[i][1];
		map[3][1] = temp;
	}
	else if (dir == 2) {
		temp = map[3][1];
		for (int i = 3; i > 0; --i)
			map[i][1] = map[i - 1][1];
		map[0][1] = temp;
	}
	else if(dir == 3) {
		temp = map[1][0];
		for(int i=0;i<=1;++i)
			map[1][i] = map[1][i+1];
		map[1][2] = map[3][1];
		map[3][1] = temp;
	}
	else {
		temp = map[1][2];
		for (int i = 2; i > 0; --i)
			map[1][i] = map[1][i - 1];
		map[1][0] = map[3][1];
		map[3][1] = temp;
	}
}
void start() {
	int dir = 1, x = 1, y = 1;
	int nx, ny, bottom;
	for (int l = 1; l <= t; ++l) {
		nx = x + dx[dir];
		ny = y + dy[dir];
		if (1 > nx || nx > n || 1 > ny || ny > m) {
			if (dir < 2) dir += 2;
			else dir -= 2;
			nx = x + dx[dir];
			ny = y + dy[dir];
		}
		make_dice(dir);
		result += (board[nx][ny] * bfs(nx, ny, board[nx][ny]));
		bottom = map[3][1];
		if (bottom > board[nx][ny] && ++dir > 3) dir = 0;
		else if (bottom < board[nx][ny] && --dir < 0) dir = 3;
		x = nx;
		y = ny;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> t;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> board[i][j];
	start();
	cout << result;
}
