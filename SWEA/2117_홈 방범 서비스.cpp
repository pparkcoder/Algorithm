#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
queue<pair<int,int> > q;
int map[21][21];
int visit[21][21];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, m, t, result, home_cnt;
void bfs(int a, int b, int num) {
	int x, y, nx, ny, k, cnt, len;
	q.push(make_pair(a, b));
	visit[a][b] = 1;
	num == 1 ? cnt = 1 : cnt = 0;
	k = 1;
	while (!q.empty()) {
		len = q.size();
		if (cnt * m - (k*k + (k - 1)*(k - 1)) >= 0) result = max(result, cnt);
		for (int j = 0; j < len; j++) {
			x = q.front().first;
			y = q.front().second; q.pop();
			for (int i = 0; i < 4; i++) {
				nx = x + dx[i];
				ny = y + dy[i];
				if (0 < nx && nx <= n && 0 < ny && ny <= n && !visit[nx][ny]) {
					if (map[nx][ny]) cnt++;
					q.push(make_pair(nx, ny));
					visit[nx][ny] = 1;
				}
			}
		}
		k++;
	}
	while (!q.empty()) q.pop();
	for (int i = 1; i < 21; i++)
		for (int j = 1; j < 21; j++)
			visit[i][j] = 0;
}
int main() {
	cin.tie(NULL); ios::sync_with_stdio(false);
	cin >> t;
	for (int l = 1; l <= t; l++) {
		result = -987654321;
		cin >> n >> m;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> map[i][j];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				bfs(i, j, map[i][j]);
		cout << "#" << l << " " << result << "\n";
	}
}
