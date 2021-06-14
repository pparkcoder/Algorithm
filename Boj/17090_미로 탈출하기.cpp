// https://www.acmicpc.net/problem/17090

#include<iostream>
#include<vector>
#define mp make_pair
using namespace std;
int visit[501][501];
char map[501][501];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int n, m;
int result = 0;
void start(int sx, int sy) {
	vector<pair<int, int> >v;
	int x, y, nx, ny, dir, flag;
	x = sx;
	y = sy;
	while (1) {
		v.push_back(mp(x, y));
		visit[x][y] = 1;
		if (map[x][y] == 'U') dir = 0;
		else if (map[x][y] == 'R') dir = 1;
		else if (map[x][y] == 'D') dir = 2;
		else dir = 3;
		nx = x + dx[dir];
		ny = y + dy[dir];
		if (1 > nx || nx > n || 1 > ny || ny > m || visit[nx][ny] == 2) {
			flag = 2;
			break;
		}
		else if (visit[nx][ny] == -2 || visit[nx][ny] == 1) {
			flag = -2;
			break;
		}
		else {
			x = nx;
			y = ny;
		}
	}
	for (int i = 0; i < v.size(); i++)
		visit[v[i].first][v[i].second] = flag;
	if (flag == 2) ++result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> map[i][j];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!visit[i][j]) start(i, j);
			else if (visit[i][j] == 2) ++result;
		}
	}
	cout << result;
}
