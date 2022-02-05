#include<iostream>
#include<algorithm>
using namespace std;
int map[21][21];
bool visit[21][21];
bool check[101];
int dx[4] = { 1,1,-1,-1 };
int dy[4] = { 1,-1,-1,1 };
int t, n, result;
void dfs(int x, int y, int sx, int sy, int cnt, int dir) {
	if (dir == 5) {
		result = max(result, cnt);
		return;
	}
	for (int i = 0; i < 2; ++i) {
		int nx = x + dx[dir + i];
		int ny = y + dy[dir + i];
		if (dir + i > 3) return;
		if (0 < nx && nx <= n && 0 < ny && ny <= n) {
			if (nx == sx && ny == sy) dfs(nx, ny, sx, sy, cnt, 5);
			else if (!visit[nx][ny] && !check[map[nx][ny]]) {
				visit[nx][ny] = check[map[nx][ny]] = 1;
				dfs(nx, ny, sx, sy, cnt + 1, dir + i);
				visit[nx][ny] = check[map[nx][ny]] = 0;
			}
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		cin >> n;
		result = -1;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				cin >> map[i][j];
		for (int i = 1; i < n; ++i) {
			for (int j = 2; j < n; ++j) {
				visit[i][j] = check[map[i][j]] = 1;
				dfs(i, j, i, j, 1, 0);
				visit[i][j] = check[map[i][j]] = 0;
			}
		}
		cout << "#" << l << " " << result << "\n";
	}
}
