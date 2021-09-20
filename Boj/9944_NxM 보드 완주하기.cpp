// https://www.acmicpc.net/problem/9944

#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int, int> >v;
char map[31][31];
int visit[31][31];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, result, spot_cnt, flag;
bool check(int x, int y) {
	if (map[x][y] == '*' || (1 > x || x > n || 1 > y || y > m) || visit[x][y]) return false;
	return true;
}
void dfs(int x, int y, int dir, int res, int cnt) {
	if (cnt == spot_cnt) {
		result = min(result, res);
		return;
	}
	int nx = x + dx[dir];
	int ny = y + dy[dir];
	if (check(nx, ny)) {
		flag = visit[nx][ny] = 1;
		dfs(nx, ny, dir, res, cnt + 1);
		visit[nx][ny] = 0;
	}
	else {
		for (int i = 0; i < 4; i++) {
			if (i == dir) continue;
			int nnx = x + dx[i];
			int nny = y + dy[i];
			if (check(nnx, nny)) {
				flag = visit[nnx][nny] = 1;
				dfs(nnx, nny, i, res + 1, cnt + 1);
				visit[nnx][nny] = 0;
			}
		}
	}
	return;
}
void init() {
	flag = 0;
	result = 987654321;
	v.clear();
}
int main() {
	ios::sync_with_stdio(false); cin.tie(0);
	for (int k = 1;; k++) {
		cin >> n >> m;
		if (cin.eof()) break;
		init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				cin >> map[i][j];
				if (map[i][j] == '.') v.push_back(make_pair(i, j));
			}
		}
		spot_cnt = v.size();
		for (int i = 0; i < spot_cnt; i++) {
			int x = v[i].first;
			int y = v[i].second;
			visit[x][y] = 1;
			for (int j = 0; j < 4; j++)
				dfs(x, y, j, 0, 1);
			visit[x][y] = 0;
		}
		cout << "Case" << " " << k << ": ";
		if (!flag) cout << 0;
		else result == 987654321 ? cout << -1 : cout << result + 1;
		cout << "\n";
	}
}
