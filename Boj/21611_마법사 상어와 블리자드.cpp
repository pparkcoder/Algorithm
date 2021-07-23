// https://www.acmicpc.net/problem/21611
// Tip -> 범위, vector 사이즈 체크가 최우선

#include<iostream>
#include<vector>
#include<cstring>
#define mp make_pair
using namespace std;
vector<pair<int, int> > v, boom;
vector<int> temp;
int map[50][50];
int counting[4];
int dx[5] = { 0,-1,1,0,0 };
int dy[5] = { 0,0,0,-1,1 };
int dx2[4] = { 0,1,0,-1 };
int dy2[4] = { -1,0,1,0 };
int n, m, d, s, sx, sy, stop;
int result = 0;
void func(int flag) {
	int x = sx, y = sy, dir = 0, now_len = 0, turn_cnt = 0, max_len = 1, cnt = 0, a = 1, index = 0;
	int nx, ny, b, tx, ty;
	while (1) {
		nx = x + dx2[dir];
		ny = y + dy2[dir];
		if (1 > nx || nx > n || 1 > ny || ny > n) break;
		if (!flag) {
			if (map[nx][ny]) temp.push_back(map[nx][ny]);
			map[nx][ny] = 0;
		}
		else if (flag == 1 && temp.size()) {
			map[nx][ny] = temp[index++];
			if (index >= temp.size()) break;
		}
		else if (flag == 2) {
			if (map[x][y] == map[nx][ny]) {
				boom.push_back(mp(x, y));
				++cnt;
			}
			else {
				if (cnt >= 3) {
					boom.push_back(mp(x, y));
					for (int i = 0; i < boom.size(); ++i) {
						tx = boom[i].first;
						ty = boom[i].second;
						++counting[map[tx][ty]];
						stop = map[tx][ty] = 0;
					}
				}
				boom.clear();
				cnt = 0;
			}
            if(!map[nx][ny]) break;
		}
		else if (flag == 3 && !(x == sx && y == sy)) {
			b = map[x][y];
			if (b == map[nx][ny]) ++a;
			else {
				temp.push_back(a);
				temp.push_back(b);
				a = 1;
			}
			if (!map[nx][ny]) {
				memset(map, 0, sizeof(map));
				break;
			}
		}
		++now_len;
		if (now_len == max_len) {
			++turn_cnt;
			now_len = 0;
			if (++dir > 3) dir = 0;
		}
		if (turn_cnt == 2) {
			++max_len;
			turn_cnt = 0;
		}
		x = nx;
		y = ny;
	}
}
void start() {
	sx = sy = (n + 1) / 2;
	for (int i = 0; i < v.size(); ++i) {
		d = v[i].first;
		s = v[i].second;
		for (int j = 1; j <= s; ++j)
			map[sx + dx[d] * j][sy + dy[d] * j] = 0;
		while (1) {
			stop = 1;
			func(0);
			func(1);
			temp.clear();
			func(2);
			if (stop) break;
		}
		func(3);
		func(1);
		temp.clear();
	}
	result = counting[1] + 2 * counting[2] + 3 * counting[3];
	cout << result;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	while (m--) {
		cin >> d >> s;
		v.push_back(mp(d, s));
	}
	start();
}
