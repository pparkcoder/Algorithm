// https://www.acmicpc.net/problem/17406

#include<iostream>
#include<algorithm>
#include<climits>
#include<vector>
using namespace std;
typedef struct {
	int r, c, s;
}info;
info I;
vector<info> v,v2;
int map[51][51], cmap[51][51];
bool visit[6];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int n, m, k, r, c, s;
int result = INT_MAX;
void show() {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			cout << map[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
}
void start() {
	int x, y, pre, now, dir, nx, ny, sum, min_x, max_x, min_y, max_y;
	for (int i = 0; i < k; ++i) {
		r = v2[i].r;
		c = v2[i].c;
		s = v2[i].s;
		for (int j = 0; j < s; ++j) {
			x = r - s + j;
			y = c - s + j;
			min_x = r - s + j;
			max_x = r + s - j;
			min_y = c - s + j;
			max_y = c + s - j;
			pre = map[x][y];
			dir = 0;
			while (1) {
				nx = x + dx[dir];
				ny = y + dy[dir];
				if (min_x > nx || nx > max_x || min_y > ny || ny > max_y) {
					++dir;
					nx = x + dx[dir];
					ny = y + dy[dir];
				}
				now = map[nx][ny];
				map[nx][ny] = pre;
				x = nx;
				y = ny;
				pre = now;
				if (x == r - s + j && y == c - s + j) break;
			}
		}
	}for (int i = 1; i <= n; ++i) {
		sum = 0;
		for (int j = 1; j <= m; ++j) {
			sum += map[i][j];
		}
		result = min(result, sum);
	}

}
void brute(int cnt) {
	if (cnt == k) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				map[i][j] = cmap[i][j];
		start();
		return;
	}
	for (int i = 0; i < k; ++i) {
		if (!visit[i]) {
			visit[i] = 1;
			v2.push_back(v[i]);
			brute(cnt + 1);
			v2.pop_back();
			visit[i] = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
			cin >> cmap[i][j];
	for (int i = 0; i < k; ++i) {
		cin >> r >> c >> s;
		I = { r,c,s };
		v.push_back(I);
	}
	brute(0);
	cout << result;
}
