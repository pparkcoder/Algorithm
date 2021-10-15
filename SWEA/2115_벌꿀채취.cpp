#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
int map[11][11];
int t, n, m, c, res, res1, res2, temp;
void find_max(int index, int x, int y, int sum1, int sum2, int flag) {
	if (flag) {
		if (sum1 > c) return;
		temp = max(temp, sum2);
	}
	for (int i = index; i < y + m; ++i)
		find_max(i + 1, x, y, sum1 + map[x][i], sum2 + pow(map[x][i], 2), 1);
}
void move(int x, int y) {
	res2 = 0;
	for (int i = x; i <= n; ++i) {
		for (int j = y; j <= n; ++j) {
			if (j + (m - 1) > n) continue;
			temp = 0;
			find_max(j, i, j, 0, 0, 0);
			res2 = max(res2, temp);
		}
		y = 1;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		cin >> n >> m >> c;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				cin >> map[i][j];
		res = res1 = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (j + (m - 1) > n) continue;
				temp = 0;
				find_max(j, i, j, 0, 0, 0);
				res1 = max(res1, temp);
				move(i, j + m);
				res = max(res, res1 + res2);
			}
		}
		cout << "#" << l << " " << res << "\n";
	}
}
