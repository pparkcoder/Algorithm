// https://www.acmicpc.net/problem/14500

#include<iostream>
#include<algorithm>
using namespace std;
int map[501][501];
bool visit[501][501];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, ans;
int result = -987654321;
void dfs(int x, int y, int cnt, int sum) {
	if (cnt == 4) {
		result = max(result, sum);
		return;
	}
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 < nx && nx <= n && 0 < ny && ny <= m && !visit[nx][ny]) {
			visit[nx][ny] = 1;
			dfs(nx, ny, cnt + 1, sum + map[nx][ny]);
			visit[nx][ny] = 0;
		}
	}
}
void bfs(int x, int y) {
	int sum = map[x][y];
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 < nx && nx <= n && 0 < ny && ny <= m) {
			sum += map[nx][ny];
			++cnt;
		}
	}
	if (cnt == 4) {
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= m) {
				ans = sum - map[nx][ny];
				result = max(result, ans);
			}
		}
	}
	else result = max(result, sum);
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> map[i][j];
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			visit[i][j] = 1;
			dfs(i, j, 1, map[i][j]);
			visit[i][j] = 0;
			if (!((i == 1 && j == 1) || (i == 1 && j == m) || (i == n && j == 1) || (i == n && j == m))) bfs(i, j);
		}
	}
	cout << result;
}
