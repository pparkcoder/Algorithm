//https://www.acmicpc.net/problem/12100

#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
vector<int> v;
int cmap[21][21], map[21][21];
bool visit[21][21];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n;
int result = 0;
void move(int x, int y, int dir) {
	int now_x = x, now_y = y;
	while (1) {
		int nx = now_x + dx[dir];
		int ny = now_y + dy[dir];
		if (1 > nx || nx > n || 1 > ny || ny > n) return;
		if (map[nx][ny]) {
			if (map[nx][ny] == map[now_x][now_y] && !visit[nx][ny]) {
				map[nx][ny] *= 2;
				map[now_x][now_y] = 0;
				visit[nx][ny] = 1;
			}
			return;
		}
		else {
			map[nx][ny] = map[now_x][now_y];
			map[now_x][now_y] = 0;
		}
		now_x = nx, now_y = ny;
	}
}
void brute(int cnt) {
	if (cnt == 5) {
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				map[i][j] = cmap[i][j];
		for (int k = 0; k < 5; ++k) {
			memset(visit, 0, sizeof(visit));
			int dir = v[k];
			if (dir == 0 || dir == 2) {
				for (int i = 1; i <= n; ++i)
					for (int j = 1; j <= n; ++j)
						if(map[i][j]) move(i, j, dir);
			}
			else {
				for (int i = n; i > 0; --i)
					for (int j = n; j > 0; --j)
						if (map[i][j]) move(i, j, dir);
			}
			for (int i = 1; i <= n; ++i)
				for (int j = 1; j <= n; ++j)
					result = max(result, map[i][j]);
		}
		return;
	}
	for (int i = 0; i < 4; ++i) {
		v.push_back(i);
		brute(cnt + 1);
		v.pop_back();
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> cmap[i][j];
	brute(0);
	cout << result;
}
