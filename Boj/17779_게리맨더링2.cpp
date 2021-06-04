// https://www.acmicpc.net/problem/17779

#include<iostream>
#include<algorithm>
#include<climits>
#include<vector>
using namespace std;
vector<int> v;
int map[21][21];
bool visit[21][21];
int dx[4] = { 1,1,-1,-1 };
int dy[4] = { 1,-1,-1,1 };
int total = 0, result = INT_MAX;
int n;
void calc(int x, int y) {
	int d1 = y, d2 = y, one = 0, two = 0, three = 0, four = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (visit[i][j]) {
				if (j < d1) d1 = j;
				if (j > d2) d2 = j;
			}
		}
	}
	d1 = y - d1;
	d2 = d2 - y;
	for (int i = 1; i < x + d1; ++i) {
		for (int j = 1; j <= y; ++j) {
			if (visit[i][j]) break;
			one += map[i][j];
		}
	}
	v.push_back(one);
	for (int i = 1; i <= x + d2; ++i) {
		for (int j = n; j > y; --j) {
			if (visit[i][j]) break;
			two += map[i][j];
		}
	}
	v.push_back(two);
	for (int i = x + d1; i <= n; ++i) {
		for (int j = 1; j < y - d1 + d2; ++j) {
			if (visit[i][j]) break;
			three += map[i][j];
		}
	}
	v.push_back(three);
	for (int i = x + d2 + 1; i <= n; ++i) {
		for (int j = n; j >= y - d1 + d2; --j) {
			if (visit[i][j]) break;
			four += map[i][j];
		}
	}
	v.push_back(four);
	v.push_back(total - (one + two + three + four));
	sort(v.begin(), v.end());
	result = min(result, v.back() - v.front());
	v.clear();
}
void dfs(int sx, int sy, int x, int y, int dir) {
	if (dir > 3 || 1 > x || x > n || 1 > y || y > n) return;
	if (visit[x][y]) {
		if (x == sx && y == sy) calc(x, y);
		return;
	}
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	visit[x][y] = 1;
	dfs(sx, sy, nx, ny, dir);
	dfs(sx, sy, nx, ny, dir + 1);
	visit[x][y] = 0;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> map[i][j];
			total += map[i][j];
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if ((i == 1 && j == 1) || (i == 1 && j == n) || (i == n && j == 1) || (i == n && j == n)) continue;
			dfs(i, j, i, j, 0);
		}
	}
	cout << result;
}
