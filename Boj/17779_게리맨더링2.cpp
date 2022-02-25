// https://www.acmicpc.net/problem/17779

#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
vector<int> v;
int map[21][21];
int check[21][21];
bool visit[21][21];
int dx[4] = { 1,1,-1,-1 };
int dy[4] = { 1,-1,-1,1 };
int total = 0, result = 987654321;
int n, d1, d2, flag1, flag2;
void find_d(int x, int y) {
	flag1 = flag2 = d1 = d2 = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (visit[j][i]) {
				d1 = j;
				flag1 = 1;
			}
		}
		if (flag1) break;
	}
	for (int i = n; i > 0; --i) {
		for (int j = n; j > 0; --j) {
			if (visit[j][i]) {
				d2 = j;
				flag2 = 1;
			}
		}
		if (flag2) break;
	}
	d1 = abs(x - d1);
	d2 = abs(x - d2);
	v.clear();
}
void calc(int x, int y) {
	find_d(x, y);
	int ans1, ans2, ans3, ans4, ans5;
	ans1 = ans2 = ans3 = ans4 = ans5 = 0;
	for (int i = 1; i < x + d1; ++i) {
		for (int j = 1; j <= y; ++j) {
			if (visit[i][j]) break;
			ans1 += map[i][j];
			check[i][j] = 1;
		}
	}
	v.push_back(ans1);
	for (int i = x + d2; i > 0; --i) {
		for (int j = n; j > y; --j) {
			if (visit[i][j]) break;
			ans2 += map[i][j];
			check[i][j] = 2;
		}
	}
	v.push_back(ans2);
	for (int i = x + d1; i <= n; ++i) {
		for (int j = 1; j < y - d1 + d2; ++j) {
			if (visit[i][j]) break;
			ans3 += map[i][j];
			check[i][j] = 3;
		}
	}
	v.push_back(ans3);
	for (int i = n; i > x + d2; --i) {
		for (int j = n; j >= y - d1 + d2; --j) {
			if (visit[i][j]) break;
			ans4 += map[i][j];
			check[i][j] = 4;
		}
	}
	v.push_back(ans4);
	ans5 = total - (ans1 + ans2 + ans3 + ans4);
	v.push_back(ans5);
	sort(v.begin(), v.end());
	result = min(result, v[v.size() - 1] - v[0]);
}
void brute(int sx, int sy, int x, int y, int dir) {
	if (dir == 5) calc(sx, sy);
	if (dir > 3) return;
	for (int i = 0; i < 2; ++i) {
		int nx = x + dx[dir + i];
		int ny = y + dy[dir + i];
		if (nx == sx && ny == sy) {
			brute(sx, sy, sx, sy, 5);
			return;
		}
		if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
			visit[nx][ny] = 1;
			brute(sx, sy, nx, ny, dir + i);
			visit[nx][ny] = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> map[i][j];
			total += map[i][j];
		}
	}
	for (int i = 1; i < n - 1; ++i) {
		for (int j = 2; j < n; ++j) {
			visit[i][j] = 1;
			brute(i, j, i, j, 0);
			visit[i][j] = 0;
		}
	}
	cout << result;
}
