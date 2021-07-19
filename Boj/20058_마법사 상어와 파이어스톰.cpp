// https://www.acmicpc.net/problem/20058

#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#define mp make_pair
using namespace std;
vector<int> v, temp;
vector<pair<int, int> >melt_v;
queue<pair<int, int> > q;
int map[65][65];
bool visit[65][65];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, Q, num, l;
int result_sum = 0, result_group = 0;
void bfs(int sx, int sy) {
	int x, y, nx, ny, cnt;
	q.push(mp(sx, sy));
	visit[sx][sy] = 1;
	cnt = 0;
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second; q.pop();
		++cnt;
		for (int i = 0; i < 4; ++i) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= n) {
				if (map[nx][ny] && !visit[nx][ny]) {
					q.push(mp(nx, ny));
					visit[nx][ny] = 1;
				}
			}
		}
	}
	result_group = max(result_group, cnt);
}
void melt() {
	melt_v.clear();
	int cnt, nx, ny;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (map[i][j]) {
				cnt = 0;
				for (int k = 0; k < 4; ++k) {
					nx = i + dx[k];
					ny = j + dy[k];
					if (0 < nx && nx <= n && 0 < ny && ny <= n && map[nx][ny] > 0)
						++cnt;
				}
				if (cnt < 3)
					melt_v.push_back(mp(i, j));
			}
		}
	}
	for (int i = 0; i < melt_v.size(); ++i) 
		--map[melt_v[i].first][melt_v[i].second];
}
void start() {
	int x, y, max_x, max_y, index;
	for (int i = 0; i < Q; ++i) {
		l = pow(2,v[i]);
		x = y = 1;
		while (1) {
			temp.clear();
			max_x = x + l;
			max_y = y + l;
			for (int j = x; j < max_x; ++j) 
				for (int k = y; k < max_y; ++k) 
					temp.push_back(map[j][k]);
			index = 0;
			for (int j = max_y - 1; j >= y; --j)
				for (int k = x; k < max_x; ++k)
					map[k][j] = temp[index++];
			y += l;
			if (y > n) {
				y = 1;
				x += l;
			}
			if (x > n) break;	
		}
		melt();
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			result_sum += map[i][j];
			if (map[i][j] && !visit[i][j])
				bfs(i, j);
		}
	}
	cout << result_sum << "\n" << result_group;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n >> Q;
	n = pow(2, n);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> map[i][j];
	for (int i = 0; i < Q; ++i) {
		cin >> num;
		v.push_back(num);
	}
	start();
}
