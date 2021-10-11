#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
typedef struct {
	int num, x, y;
}info;
info I;
vector<info> v;
int map[9][9];
bool visit[9][9];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int t, n, k, result, temp;
void dfs(int num, int x, int y, int flag, int cnt) {
	result = max(result, cnt);
	for (int i = 0; i < 4; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
			if (map[nx][ny] < num) {
				visit[nx][ny] = 1;
				dfs(map[nx][ny], nx, ny, flag, cnt + 1);
				visit[nx][ny] = 0;
			}
			else {
				if (!flag) {
					for (int j = 1; j <= k; ++j) {
						if (map[nx][ny] - j < num) {
							map[nx][ny] -= j;
							visit[nx][ny] = 1;
							dfs(map[nx][ny], nx, ny, 1, cnt + 1);
							visit[nx][ny] = 0;
							map[nx][ny] += j;
						}
					}
				}
			}
		}
	}
	return;
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		v.clear();
		temp = result = 0;
		cin >> n >> k;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				cin >> map[i][j];
				temp = max(temp, map[i][j]);
			}
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (map[i][j] == temp) {
					I = { temp,i,j };
					v.push_back(I);
				}
			}
		}
		for (int i = 0; i < v.size(); ++i) {
			int x = v[i].x;
			int y = v[i].y;
			visit[x][y] = 1;
			dfs(v[i].num, x, y, 0, 1);
			visit[x][y] = 0;
		}
		cout << "#" << l << " " << result << "\n";
	}
}
