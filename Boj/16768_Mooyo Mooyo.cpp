// https://www.acmicpc.net/problem/16768

#include<iostream>
#include<vector>
#include<queue>
#define mp make_pair
using namespace std;
queue<pair<int, int> >q;
vector<pair<int, int> >v;
vector<char> temp;
char map[101][11];
int visit[101][11];
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
int n, k, stop;
int num = 1;
void bfs(int a, int b, char value) {
	int x, y, nx, ny, len;
	q.push(mp(a, b));
	visit[a][b] = num;
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second; q.pop();
		v.push_back(mp(x, y));
		for (int i = 0; i < 4; i++) {
			nx = x + dx[i];
			ny = y + dy[i];
			if (0 < nx && nx <= n && 0 < ny && ny <= 10) {
				if (map[nx][ny] == value && visit[nx][ny] != num) {
					q.push(mp(nx, ny));
					visit[nx][ny] = num;
				}
			}
		}
	}
	len = v.size();
	if (len >= k) {
		stop = 0;
		for (int i = 0; i < len; i++)
			map[v[i].first][v[i].second] = '0';
	}
	v.clear();
}
void down() {
	for (int i = 1; i <= 10; ++i) {
		for (int j = n; j > 0; --j) {
			if (map[j][i] != '0') {
				temp.push_back(map[j][i]);
				map[j][i] = '0';
			}
		}
		if (temp.size()) {
			int index = 0;
			for (int j = n; j > 0; --j) {
				map[j][i] = temp[index++];
				if (index >= temp.size()) break;
			}
			temp.clear();
		}
	}
}
int main() {
	cin.tie(0); ios::sync_with_stdio(0);
	cin >> n >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= 10; j++)
			cin >> map[i][j];
	while (1) {
		stop = 1;
		for (int i = n; i > 0; i--) {
			for (int j = 10; j > 0; j--) {
				if ('1' <= map[i][j] && map[i][j] <= '9' && visit[i][j] != num) {
					bfs(i, j, map[i][j]);
					num++;
				}
			}
		}
		if (stop) break;
		down();
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= 10; j++)
			cout << map[i][j];
		cout << "\n";
	}
}
