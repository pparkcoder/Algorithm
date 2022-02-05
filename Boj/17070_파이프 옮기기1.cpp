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

/*
#include<iostream>
using namespace std;
int map[17][17];
int dx[3] = { 0,1,1 };
int dy[3] = { 1,0,1 };
int n;
int result = 0;
bool check(int x, int y) {
	for (int i = 0; i < 2; ++i) {
		int nx = x - dx[i];
		int ny = y - dy[i];
		if (1 > nx || nx > n || 1 > ny || ny > n || map[nx][ny]) return false;
	}
	return true;
}
void dfs(int x, int y, int dir) {
	if (x == n && y == n) {
		++result;
		return;
	}
	for (int i = 0; i < 3; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if ((dir == 0 && i == 1) || (dir == 1 && i == 0)) continue;
		if (i == 2 && !check(nx, ny)) continue;
		if (0 < nx && nx <= n && 0 < ny && ny <= n && !map[nx][ny]) dfs(nx, ny, i);
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	dfs(1, 2, 0);
	cout << result;
}
*/

