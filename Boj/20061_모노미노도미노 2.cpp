// https://www.acmicpc.net/problem/20061
// Tip -> 연한부분은 찾고 break 후 다시 찾기

#include<iostream>
#include<vector>
using namespace std;
vector<int> v;
int map[10][10];
int dx[2] = { 1,0 };
int dy[2] = { 0,1 };
int n;
int score = 0;
void down(int color, int limit) {
	int index = 0;
	if (!color) {
		for (int i = 4; i < limit; ++i) {
			for (int j = 0; j < 4; ++j) {
				v.push_back(map[i][j]);
				map[i][j] = 0;
			}
		}
		for (int i = 5; i <= limit; ++i)
			for (int j = 0; j < 4; ++j)
				map[i][j] = v[index++];
	}
	else {
		for (int i = 4; i < limit; ++i) {
			for (int j = 0; j < 4; ++j) {
				v.push_back(map[j][i]);
				map[j][i] = 0;
			}
		}
		for (int i = 5; i <= limit; ++i)
			for (int j = 0; j < 4; ++j)
				map[j][i] = v[index++];
	}
	v.clear();
}
void blue(int t, int sx, int sy) {
	int x = sx, y = sy;
	int nx, ny, cnt;
	if (t == 2) y += 1;
	while (1) {
		nx = x + dx[1];
		ny = y + dy[1];
		if (0 > nx || nx > 9 || 0 > ny || ny > 9 || map[nx][ny]) break;
		if (t == 3 && map[nx+1][ny]) break;
		x = nx;
		y = ny;
	}
	map[x][y] = 1;
	if (t == 2) map[x][y-1] = 1;
	else if (t == 3) map[x+1][y] = 1;

	// 가득찬 열 찾기
	for (int i = 9; i > 5; --i) {
		cnt = 0;
		for (int j = 0; j < 4; ++j)
			if (map[j][i]) ++cnt;
		if (cnt == 4) {
			for (int j = 0; j < 4; ++j)
				map[j][i] = 0;
			++score;
			down(1, i);
			++i;
		}
	}
	//연한부분 찾기
	for (int i = 5; i > 3; --i) {
		for (int j = 0; j < 4; ++j)
			if (map[j][i]) {
				for (int k = 0; k < 4; ++k)
					map[k][9] = 0;
				down(1, 9);
				++i;
				break;
			}
	}
}
void green(int t, int sx, int sy) {
	int x = sx, y = sy;
	int nx, ny, cnt;
	if (t == 3) x += 1;
	while (1) {
		nx = x + dx[0];
		ny = y + dy[0];
		if (0 > nx || nx > 9 || 0 > ny || ny > 9 || map[nx][ny]) break;
		if (t == 2 && map[nx][ny + 1]) break;
		x = nx;
		y = ny;
	}

	map[x][y] = 1;
	if (t == 3) map[x - 1][y] = 1;
	else if (t == 2) map[x][y + 1] = 1;

	// 가득찬 행 찾기
	for (int i = 9; i > 5; --i) {
		cnt = 0;
		for (int j = 0; j < 4; ++j)
			if (map[i][j]) ++cnt;
		if (cnt == 4) {
			for (int j = 0; j < 4; ++j)
				map[i][j] = 0;
			++score;
			down(0, i);
			++i;
		}
	}
	//연한부분 찾기
	for (int i = 5; i > 3; --i) {
		for (int j = 0; j < 4; ++j)
			if (map[i][j]) {
				for (int k = 0; k < 4; ++k)
					map[9][k] = 0;
				down(0, 9);
				++i;
				break;
			}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	while (n--) {
		int t, x, y;
		cin >> t >> x >> y;
		green(t, x, y);
		blue(t, x, y);
	}
	int sum = 0;
	for (int i = 6; i < 10; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (map[i][j]) ++sum;
			if (map[j][i]) ++sum;

		}
	}
	cout << score << "\n" << sum;
}
