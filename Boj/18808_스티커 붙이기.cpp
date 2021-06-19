// https://www.acmicpc.net/problem/18808

#include<iostream>
#include<vector>
#define mp make_pair
using namespace std;
vector<pair<int, int> > info;
vector<int> v;
int sticker[101][11][11];
int map[41][41];
int n, m, k;
int result = 0;
void turn(int len_x, int len_y, int num) {
	for (int i = 1; i <= len_x; ++i) {
		for (int j = 1; j <= len_y; ++j) {
			v.push_back(sticker[num][i][j]);
			sticker[num][i][j] = 0;
		}
	}
	int index = 0, temp = len_x;
	len_x = len_y;
	len_y = temp;
	for (int i = len_y; i > 0; --i)
		for (int j = 1; j <= len_x; ++j)
			sticker[num][j][i] = v[index++];
	info[num - 1].first = len_x;
	info[num - 1].second = len_y;
	v.clear();
}
bool check(int len_x, int len_y, int sx, int sy, int num) {
	for (int i = sx, x = 1; i < sx + len_x; ++i, ++x) {
		for (int j = sy, y = 1; j < sy + len_y; ++j, ++y) {
			if (1 > i || i > n || 1 > j || j > m) return false;
			if (sticker[num][x][y] && map[i][j]) return false;
		}
	}
	for (int i = sx, x = 1; i < sx + len_x; ++i, ++x) {
		for (int j = sy, y = 1; j < sy + len_y; ++j, ++y) {
			if (sticker[num][x][y]) {
				map[i][j] = 1;
				++result;
			}
		}
	}
	return true;
}
void start() {
	int len_x, len_y, flag, cnt;
	for (int num = 1; num <= k; ++num) {
		flag = cnt = 0;
		while (1) {
			len_x = info[num - 1].first;
			len_y = info[num - 1].second;
			for (int i = 1; i <= n; ++i) {
				for (int j = 1; j <= m; ++j) {
					if (check(len_x, len_y, i, j, num)) {
						flag = 1;
						break;
					}
				}
				if (flag) break;
			}
			if (cnt == 3 || flag) break;
			++cnt;
			turn(len_x, len_y, num);
		}
	}
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	int r, c;
	for (int i = 1; i <= k; ++i) {
		cin >> r >> c;
		for (int j = 1; j <= r; ++j)
			for (int l = 1; l <= c; ++l)
				cin >> sticker[i][j][l];
		info.push_back(mp(r, c));
	}
	start();
}
