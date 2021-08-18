// https://www.acmicpc.net/problem/2234

#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#define mp make_pair
using namespace std;
queue<pair<int, int> >q;
vector<int> v;
int map[51][51][4];
int visit[51][51];
int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };
int room_cnt = 0, result_size = 0, result_maxsize = 0, check_num = 1;
int m, n;
void make_wall(int x, int y, int num) {
	int temp;
	for (int i = 0; i < 4; i++) {
		temp = num % 2;
		num /= 2;
		map[x][y][i] = temp;
	}
}
void find_max() {
	int nx, ny;
	for (int x = 1; x <= m; x++) {
		for (int y = 1; y <= n; y++) {
			for (int k = 0; k < 4; k++) {
				nx = x + dx[k];
				ny = y + dy[k];
				if (0 < nx && nx <= m && 0 < ny && ny <= n && visit[x][y] != visit[nx][ny])
					result_maxsize = max(result_maxsize, v[visit[x][y] - 1] + v[visit[nx][ny] - 1]);
			}
		}
	}
}
void bfs(int sx, int sy) {
	while (!q.empty()) q.pop();
	q.push(mp(sx, sy));
	visit[sx][sy] = check_num;
	int size = 0;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second; q.pop();
		++size;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (0 < nx && nx <= m && 0 < ny && ny <= n) {
				if (!map[x][y][i] && !visit[nx][ny]) {
					q.push(mp(nx, ny));
					visit[nx][ny] = check_num;
				}
			}
		}
	}
	v.push_back(size);
	result_size = max(result_size, size);
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int num;
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> num;
			make_wall(i, j, num);
		}
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (!visit[i][j]) {
				bfs(i, j);
				++check_num;
				++room_cnt;
			}
		}
	}
	find_max();
	cout << room_cnt << "\n" << result_size << "\n" << result_maxsize;
}
