#include<iostream>
#include<algorithm>
using namespace std;
int map[21][21];
int dx[4] = { 1,1,-1,-1 };
int dy[4] = { 1,-1,-1,1 };
int check[101];
int t, n, result, sx, sy;
void dfs(int x, int y ,int dir, int cnt) {
	if (x == sx && y == sy && dir == 3) {
		result = max(result, cnt);
		return;
	}
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	if (nx == sx && ny == sy) dfs(nx, ny, dir, cnt);
	else if (0 < nx && nx <= n && 0 < ny && ny <= n && !check[map[nx][ny]]) {
		check[map[nx][ny]] = 1;
		dfs(nx, ny, dir, cnt + 1);
		dfs(nx, ny, dir + 1, cnt + 1);
		check[map[nx][ny]] = 0;
	}
}
int main() {
	cin.tie(0); ios::sync_with_stdio(0);
	cin >> t;
	for (int l = 1; l <= t; l++) {
		cin >> n;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> map[i][j];
		result = -1;
		for (int i = 1; i <= n; i++) {
			for (int j = 2; j < n; j++) {
				sx = i, sy = j;
				check[map[i][j]] = 1;
				dfs(i, j, 0, 1);
				check[map[i][j]] = 0;
			}
		}
		cout << "#" << l << " " << result << "\n";
	}
}
