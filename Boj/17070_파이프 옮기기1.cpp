#include<iostream>
using namespace std;
int map[17][17];
int n;
int result = 0;
void dfs(int dir, int x, int y) {
	if (1 > x || x > n || 1 > y || y > n) return;
	if (x == n && y == n) {
		result++;
		return;
	}
	if (dir == 0) {
		if (!map[x][y + 1]) dfs(0, x, y + 1);
		if (!map[x][y + 1] && !map[x + 1][y] && !map[x + 1][y + 1]) dfs(2, x + 1, y + 1);
	}
	else if (dir == 1) {
		if (!map[x + 1][y]) dfs(1, x + 1, y);
		if (!map[x][y + 1] && !map[x + 1][y] && !map[x + 1][y + 1]) dfs(2, x + 1, y + 1);
	}
	else {
		if (!map[x][y + 1]) dfs(0, x, y + 1);
		if (!map[x + 1][y]) dfs(1, x + 1, y);
		if (!map[x][y + 1] && !map[x + 1][y] && !map[x + 1][y + 1]) dfs(2, x + 1, y + 1);
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			cin >> map[i][j];
	dfs(0, 1, 2);
	cout << result;
}
