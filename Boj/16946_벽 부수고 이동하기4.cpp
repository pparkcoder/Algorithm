// https://www.acmicpc.net/problem/16946

#include<iostream>
#include<queue>
#include<vector>
#include<map>
#define mp make_pair
using namespace std;
vector<pair<int, int> > v;
queue<pair<int, int> > zero, one;
pair<int, int> visit[1001][1001];
int result[1001][1001];
char board[1001][1001];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m;
int num = 1;
void zero_bfs(int sx, int sy) {
	zero.push(mp(sx, sy));
	visit[sx][sy].first = num;
	int x, y, nx, ny, cnt;
	cnt = 0;
	while (!zero.empty()) {
		x = zero.front().first;
		y = zero.front().second; zero.pop();
		v.push_back(mp(x, y));
		++cnt;
		for (int i = 0; i < 4; ++i) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m && !visit[nx][ny].first && board[nx][ny] == '0') {
				zero.push(mp(nx, ny));
				visit[nx][ny].first = num;
			}
		}
	}
	for (int i = 0; i < v.size(); ++i)
		visit[v[i].first][v[i].second].second = cnt;
	v.clear();
}
void one_bfs() {
	int x, y, nx, ny;
	while (!one.empty()) {
		map<int, int> check;
		x = one.front().first;
		y = one.front().second; one.pop();
		result[x][y] = 1;
		for (int i = 0; i < 4; ++i) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m && !check[visit[nx][ny].first] && board[nx][ny] == '0') {
				result[x][y] += visit[nx][ny].second;
				check[visit[nx][ny].first] = 1;
			}
		}
		result[x][y] %= 10;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			cout << result[i][j];
		cout << "\n";
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> board[i][j];
			if (board[i][j] == '1') one.push(mp(i, j));
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (board[i][j] == '0' && !visit[i][j].first) {
				zero_bfs(i, j);
				++num;
			}
		}
	}
	one_bfs();
}
