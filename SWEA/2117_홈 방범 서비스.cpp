#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
#define mp make_pair
using namespace std;
queue<pair<int, int> > q;
int map[21][21];
bool visit[21][21];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int t, n, m, result;
void bfs(int sx, int sy) {
	q.push(mp(sx, sy));
	visit[sx][sy] = 1;
	int k = 1, house = 0;
	while (1) {
		int len = q.size();
		while (len--) {
			int x = q.front().first;
			int y = q.front().second; q.pop();
			if (map[x][y]) ++house;
			for (int i = 0; i < 4; ++i) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
					q.push(mp(nx, ny));
					visit[nx][ny] = 1;
				}
			}
		}
		if (m * house - (k*k + (k - 1)*(k - 1)) >= 0) result = max(result, house);
		if (q.empty()) break;
       		++k;
	}
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> t;
	for (int l = 1; l <= t; ++l) {
		cin >> n >> m;
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				cin >> map[i][j];
		result = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				bfs(i, j);
				memset(visit, 0, sizeof(visit));
			}
		}
		cout << "#" << l << " " << result << "\n";
	}
}
